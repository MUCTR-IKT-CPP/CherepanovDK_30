#include "include.h"


int main() {
    Machine machine;
    machine.addDetail(std::make_shared<Motor>(100, 10, 10, 100));
    machine.addDetail(std::make_shared<Shaft>(100, 10, 10, 100));
    machine.addDetail(std::make_shared<CuttingHead>(100, 10, 10, 100));
    
    Machine machine2;
    machine2.addDetail(std::make_shared<Motor>(100, 10, 10, 100));
    machine2.addDetail(std::make_shared<ControlPanel>(100, 10, 10, 100));

    Workshop workshop;
    workshop.addMachine(std::make_shared<Machine>(machine));
    workshop.addMachine(std::make_shared<Machine>(machine2));
    workshop.work();

    std::cout << workshop;

    return 0;

}