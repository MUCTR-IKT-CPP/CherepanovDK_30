#include <unordered_map>

class YearStatistics {
    private:
        std::string year;
        int maxMachineIdle = 0;
        int sumMachineIdle = 0;
        int sumReplaceCount = 0;
        int sumRepairCost = 0;
        int sumBrokeCount = 0;
        std::unordered_map<std::string, int> machinesBrokeCounts;

    public:
        YearStatistics(std::string year,
         int maxMachineIdle,
         int sumMachineIdle,
         int sumReplaceCount,
         int sumRepairCost,
         int sumBrokeCount,
         std::unordered_map<std::string, int> machinesBrokeCounts)
        : maxMachineIdle(maxMachineIdle), sumMachineIdle(sumMachineIdle),
         sumReplaceCount(sumReplaceCount), sumRepairCost(sumRepairCost),
         sumBrokeCount(sumBrokeCount), machinesBrokeCounts(machinesBrokeCounts) {}

        friend std::ostream& operator<<(std::ostream& out, const YearStatistics& statistics) {
            out << "Year: " << statistics.year << " | max machine idle: " << statistics.maxMachineIdle
            << " | sum machine idle: " << statistics.sumMachineIdle
            << " | sum replace count: " << statistics.sumReplaceCount
            << " | sum repair cost: " << statistics.sumRepairCost
            << " | sum broke count: " << statistics.sumBrokeCount
            << " | machines broke counts: " << statistics.machinesBrokeCounts;
            return out;
        }

}