#include <vector>
#include <memory>
#include <ctime>
class ShootingRange {
    private:
        std::shared_ptr<Gun> gun;
        std::vector<std::shared_ptr<Target>> targets;
        std::vector<std::shared_ptr<Statistics>> statistics;
        double chanceToBurst;
        int destroyedTargets = 0;
        double avgDamage = 0.0;
        int totallHits = 0;
        int totalDamage = 0;
        int totalShots = 0;

    public:

        ShootingRange(std::shared_ptr<Gun> gun, double chanceToBurst) : gun(gun), chanceToBurst(chanceToBurst) {}

        void addTarget(std::shared_ptr<Target> target) {
            targets.push_back(target);
        }

        void generateRandomTargets() {
            int numTargets = std::rand() % 4 + 1;
            for (int i = 0; i < numTargets; i++) {
                int targetClass = std::rand() % 3;
                if (targetClass == 0) {
                    targets.push_back(std::make_shared<StandardTarget>(generateRandomDistance(), generateRandomSize(), generateRandomHealth()));
                } else if (targetClass == 1) {
                    targets.push_back(std::make_shared<MovingTarget>(generateRandomDistance(), generateRandomSize(), generateRandomHealth(), generateRandomSpeed()));
                } else {
                    targets.push_back(std::make_shared<StandardTarget>(generateRandomDistance(), generateRandomSize(), generateRandomHealth()));
                    targets.push_back(std::make_shared<MovingTarget>(generateRandomDistance(), generateRandomSize(), generateRandomHealth(), generateRandomSpeed()));
                }
            }
            std::cout << "Generated " << targets.size() << " targets" << std::endl;
            printTargets();
        }

        int generateRandomDistance() {
            return std::rand() % 10 + 1;
        }

        int generateRandomSize() {
            return std::rand() % 10 + 1;
        }

        int generateRandomHealth() {
            return std::rand() % 100 + 50;
        }

        int generateRandomSpeed() {
            return std::rand() % 10 + 1;
        }

        void printTargets() {
            for (auto& target : targets) {
                std::cout << *target << std::endl;
            }
        }
        
        void simulate() {


            for (int i = 0; i < 60; i++) {
                

                for (auto target : targets) {

                    if (target->isAlive()) {
                        if (chanceToBurst >= gun->getBurstChance()) {
                            int damage = gun->burstShot(target->getHitDifficulty());
                            if (damage > 0) {
                                target->reduceHealth(damage);
                                totalDamage += damage;
                                totallHits+= gun->getBurstSize();
                                
                                if (!target->isAlive()) {
                                    destroyedTargets++;
                                }
                            }
                            totalShots+= gun->getBurstSize();

                        } else {
                            int damage = gun->singleShot(target->getHitDifficulty());

                            if (damage > 0) {
                                target->reduceHealth(damage);
                                totalDamage += damage;
                                totallHits++;
                                if (!target->isAlive()) {
                                    destroyedTargets++;
                                }
                            }
                            totalShots++;

                        }
                    }
                }
            }
            avgDamage = (double)totalDamage / (double)totalShots;
        }

        friend std::ostream& operator<<(std::ostream& os, const ShootingRange& sr) {
            os << "ShootingRange: " << "Destroyed Targets: " << sr.destroyedTargets << ", Avg. Damage: " 
            << sr.avgDamage << ", Total Hits: " << sr.totallHits << ", Total Shots: " << sr.totalShots;
            return os;
        }

};