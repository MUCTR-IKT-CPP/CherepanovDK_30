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

        /**
         * Generates a random percentage value from 0 to 100.
         * Used to simulate the probability of a machine breaking.
         * @return a random percentage value
         */
        int generatePercent() {
            return rand() % 101;
        }

    public:

        /**
         * Adds a detail to the machine's list of details.
         *
         * @param detail a shared pointer to the detail to be added
         */
        void addDetail(std::shared_ptr<Detail> detail) {
            details.push_back(detail);
        }

        /**
         * Simulates the work of the machine.
         *
         * @param hours the number of hours the machine works
         * @param intense the intensity of the work
         */
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

        /**
         * Gets the number of times the machine broke during its work.
         * 
         * @return the number of times the machine broke
         */
        int getBrokeCount() {
            return brokeCount;
        }

        /**
         * Gets the total time the machine was idle due to broken details.
         * 
         * @return the total time the machine was idle
         */
        int getTotalIdleTime() {
            return totalIdleTime;
        }

        /**
         * Gets the number of times the machine's details were replaced during its work.
         * 
         * @return the number of times the machine's details were replaced
         */
        int getReplaceCount() {
            return detailReplaceCount;
        }

        /**
         * Gets the total cost of repair of the machine's details during its work.
         * 
         * @return the total cost of repair
         */
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