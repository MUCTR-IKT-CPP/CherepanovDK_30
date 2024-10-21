#include <vector>
#include <memory>
#include <ctime>
class ShootingRange {
    private:
        int round = 1;
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

        /**
         * Generates a random number of targets between 1 and 4.
         * Each target is randomly chosen to be either a StandardTarget or a MovingTarget.
         * The distance, size, health and speed of each target are also randomly generated.
         * The targets are added to the ShootingRange and then printed out.
         */
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
            return std::rand() % 5 + 1;
        }

        void printTargets() {
            for (auto& target : targets) {
                std::cout << *target << std::endl;
            }
            std::cout << std::endl;
        }
        
        /**
        * Simulates the shooting range for 60 rounds.
        * Each round, iterates through the targets and checks if they are alive.
        * If the chance to burst shot is met, performs a burst shot using the gun and reduces the target's health.
        * If the target is destroyed, updates statistics and marks the target as destroyed.
        * If the chance to burst shot is not met, performs a single shot using the gun and updates statistics accordingly.
        * Calculates average damage, creates round statistics, and resets the statistics for the next round.
        */
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
                                    target->destroy();
                                    target->setDestructionRound(round);
                                    destroyedTargets++;
                                }
                            }
                            totalShots++;
                        }
                    }
                }
            }
            avgDamage = (double)totalDamage / (double)totalShots;
            std::shared_ptr<Statistics> roundStatistics = std::make_shared<Statistics>(round, totalDamage, totalShots, totallHits, destroyedTargets, avgDamage);
            statistics.push_back(roundStatistics);
            std::cout << "Round " << round << " completed" << std::endl;
            std::cout << "Round statistics: " << *roundStatistics << std::endl;
            round++;
            resetStatistics();
        }

        /**
         * Resets all statistics to zero.
         *
         * This function should be called before each new round of simulation.
         */
        void resetStatistics() {
            destroyedTargets = 0;
            avgDamage = 0.0;
            totallHits = 0;
            totalDamage = 0;
            totalShots = 0;
        }

        /**
         * Prints all round statistics stored in the ShootingRange object to the standard output.
         *
         * This function iterates over the statistics vector and prints each round's statistics
         * using the Statistics class's overloaded operator<< output stream operator.
         */
        void printStatistics() {
            for (auto& stat : statistics) {
                std::cout << *stat << std::endl;
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const ShootingRange& sr) {
            os << "ShootingRange: " << std::endl;
            for (auto& target : sr.targets) {
                os << *target << std::endl;
            }
            os << "Statistics: ";
            for (auto& stat : sr.statistics) {
                os << *stat << std::endl;
            }
            return os;
        }

};