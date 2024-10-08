#include "include.h"

void printMenu() {
    std::cout << "1 - Add machine" << std::endl;
    std::cout << "2 - Work" << std::endl;
    std::cout << "3 - Get statistics" << std::endl;
    std::cout << "0 - Exit" << std::endl;
}


void addDetail(Machine& machine) {
    std::cout << "Select detail Type (1 - Motor, 2 - Shaft, 3 - CuttingHead, 4 - ControlPanel)" << std::endl;
    int detailType;
    std::cin >> detailType;
    std::cout << "Enter detail replace price" << std::endl;
    int replacePrice;
    std::cin >> replacePrice;
    std::cout << "Enter detail repair price" << std::endl;
    int repairPrice;
    std::cin >> repairPrice;
    std::cout << "Enter detail repair time (hours)" << std::endl;
    int repairTime;
    std::cin >> repairTime;
    std::cout << "Enter detail nominal lifetime (hours)" << std::endl;
    int nominalLifetime;
    std::cin >> nominalLifetime;
    switch (detailType) {
        case 1:
            machine.addDetail(std::make_shared<Motor>(replacePrice, repairPrice, repairTime, nominalLifetime));
            break;
        case 2:
            machine.addDetail(std::make_shared<Shaft>(replacePrice, repairPrice, repairTime, nominalLifetime));
            break;
        case 3:
            machine.addDetail(std::make_shared<CuttingHead>(replacePrice, repairPrice, repairTime, nominalLifetime));
            break;
        case 4:
            machine.addDetail(std::make_shared<ControlPanel>(replacePrice, repairPrice, repairTime, nominalLifetime));
            break;
    }
}

Machine createMachine() {
    Machine machine;
    machine.addDetail(std::make_shared<Motor>(100, 10, 10, 100));
    while (true) {
        std::cout << "You want to add additional detail? (y/n)" << std::endl;
        char answer;
        std::cin >> answer;
        if (answer == 'y') {
        addDetail(machine);
        } else {
            break;
        }
    }
   
    return machine;
}

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

    while (true) {
        printMenu();
        int command;
        std::cin >> command;
        switch (command) {
            case 1: 
                workshop.addMachine(std::make_shared<Machine>(createMachine()));
                break;
            case 2:
                workshop.work();
                break;
            case 3:
                std::cout << workshop << std::endl;
                break;
            case 0:
                return 0;
        }
    }

    return 0;

}