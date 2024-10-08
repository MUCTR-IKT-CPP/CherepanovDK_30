
class Workshop {
    private:
        int maxMachineIdle = 0;
        int sumMachineIdle = 0;
        int sumReplaceCount = 0;
        int sumRepairCost = 0;
        int sumBrokeCount = 0;
        std::vector<Machine> machines;

    public:
        void addMachine(std::shared_ptr<Machine> machine) {
            machines.push_back(*machine);
        }

        double calculateIntensity() {
            return static_cast<double>(rand()) / RAND_MAX;;
        }

        void work() {
            for (int i = 0; i < 365; i++) {
                double intense = calculateIntensity();
                if (i % 30 == 0) {
                    intense = calculateIntensity();
                }

                for (auto& machine : machines) {
                    machine.work(12, intense);
                }
            }

            getStatistics();
        }

        void getStatistics() {
            for (auto& machine : machines) {
                sumMachineIdle += machine.getTotalIdleTime();
                sumReplaceCount += machine.getReplaceCount();
                sumRepairCost += machine.getRepairCost();
                sumBrokeCount += machine.getBrokeCount();
                if (machine.getTotalIdleTime() > maxMachineIdle) {
                    maxMachineIdle = machine.getTotalIdleTime();
                }
            }
        }


        friend std::ostream& operator<<(std::ostream& os, const Workshop& workshop) {
            os << "Workshop Statistics: \n" <<"Max machine idle time: " << workshop.maxMachineIdle 
            << " | Replace count: " << workshop.sumReplaceCount << " | Repair cost: "
            << workshop.sumRepairCost << " | Broke count: " << workshop.sumBrokeCount 
            << " | Sum idle time: " << workshop.sumMachineIdle << "\nMachines:" << std::endl;
            for (auto& machine : workshop.machines) {
                os << machine << std::endl;
            }
            return os;
        }
};