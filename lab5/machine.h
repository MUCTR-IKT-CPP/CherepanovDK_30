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
            return rand() % 101;
        }

    public:

        void addDetail(std::shared_ptr<Detail> detail) {
            details.push_back(detail);
        }

        void work(int hours, int intense) {
            srand(time(0));
            int chanceToBroke = generatePercent();

            for (int i = 0; i < hours; i++) {

                for (auto& detail : this->details) {

                    int chanceToBrokeDetail = generatePercent();

                    int currentIdle = detail->work(intense);
                  
                    if (chanceToBrokeDetail < chanceToBroke) {
                        

                        if (currentIdle != 0) {
                            detailReplaceCount++;
                            resultRepairCost += detail->replace();
                            totalIdleTime += detailReplaceTime;
                            i += detailReplaceTime;
                        }
                    } else {
                        brokeCount++;
                        resultRepairCost += detail->repair();
                        totalIdleTime += detail->getRepairTime();
                        i += currentIdle;
                    }
                }
            }
        }

        int getBrokeCount() {
            return brokeCount;
        }

        int getTotalIdleTime() {
            return totalIdleTime;
        }

        int getReplaceCount() {
            return detailReplaceCount;
        }

        int getRepairCost() {
            return resultRepairCost;
        }

        friend std::ostream& operator<<(std::ostream& out, const Machine& machine) {
            out << "MachineClass: " << typeid(machine).name() << " | object data: "  <<" detail replace count:"  << machine.detailReplaceCount 
            << " | result repair cost:" << machine.resultRepairCost << " | idle time:" << machine.totalIdleTime 
            << " | broke count:" << machine.brokeCount << std::endl;
            return out;
        }


};