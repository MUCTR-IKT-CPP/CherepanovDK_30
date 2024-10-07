#include <random>
#include <memory>
#include <cstdlib>
#include <ctime>

class Machine {
    private:
        int detailReplaceTime = 4;
        int detailReplaceCount = 0;
        int resultRepairCost = 0;
        int totalIdleTime = 0;
        int brokeCount = 0;
        std::vector<std::shared_ptr<Detail>> details;

        int generatePercent() {
            // std::random_device rd; 
            // std::mt19937 gen(rd()); 

            // std::uniform_int_distribution<> dist(0, 100);

            // return dist(gen);


            return rand() % 101;
        }

    public:

        void addDetail(std::shared_ptr<Detail> detail) {
            details.push_back(detail);
        }

        void work(int hours, int intense) {
            srand(time(0));
            int chanceToBroke = generatePercent();
            std::cout << "Limit of Chance to broke: " << chanceToBroke << std::endl;

            for (int i = 0; i < hours; i++) {

                for (auto& detail : this->details) {

                    int chanceToBrokeDetail = generatePercent();
                    //std::cout << "Chance to broke: " << chanceToBrokeDetail << std::endl;
                    int currentIdle = detail->work(intense);
                    if (chanceToBrokeDetail < chanceToBroke) {
                        
                        std::cout << "Detail " << typeid(*detail).name() << " was idle " << currentIdle << std::endl;
                        if (currentIdle != 0) {
                            detailReplaceCount++;
                            resultRepairCost += detail->replace();
                            totalIdleTime += detailReplaceTime;
                            i += detailReplaceTime;
                        }
                    } else {
                        std::cout << "Chance to broke: " << chanceToBrokeDetail << std::endl;
                        std::cout << "Detail " << typeid(*detail).name() << " was broken" << std::endl;
                        brokeCount++;
                        resultRepairCost += detail->repair();
                        totalIdleTime += detail->getRepairTime();
                        i += currentIdle;
                    }
                }
            }
        }

        friend std::ostream& operator<<(std::ostream& out, const Machine& machine) {
            out << "MachineClass: " << typeid(machine).name() << " | object data: "  <<" detail replace count:"  << machine.detailReplaceCount 
            << " result repair cost:" << machine.resultRepairCost << " idle time:" << machine.totalIdleTime 
            << " broke count:" << machine.brokeCount << std::endl;
            return out;
        }


};