#include "include.h"
#include <memory>

void menu() {

    std::cout << "1 - Add target" << std::endl;
    std::cout << "2 - Start simulation" << std::endl;
    std::cout << "3 - Print statistics" << std::endl;
    std::cout << "4 - Generate new targets" << std::endl;
    std::cout << "0 - Exit" << std::endl;
}

std::shared_ptr<Target> createTarget() {

    std::cout << "1 - Standard target" << std::endl;
    std::cout << "2 - Moving target" << std::endl;
    int choice;
    std::cin >> choice;
    int distance;
    int size;
    int health;
    switch (choice) {
        case 1:
            std::cout << "Enter distance: ";
            std::cin >> distance;
            std::cout << "Enter size: ";
            std::cin >> size;
            std::cout << "Enter health: ";
            std::cin >> health;
            return std::make_shared<StandardTarget>(distance, size, health);
        case 2:
            std::cout << "Enter distance: ";
            std::cin >> distance;
            std::cout << "Enter size: ";
            std::cin >> size;
            std::cout << "Enter health: ";
            std::cin >> health;
            int speed;
            std::cout << "Enter speed: ";
            std::cin >> speed;
            return std::make_shared<MovingTarget>(distance, size, health, speed);
        default:
            std::cout << "Invalid choice" << std::endl;
            return nullptr;
    }
}

int main() {

    std::srand(std::time(0));

    ShootingRange shootingRange(std::make_shared<Gun>(30, 3, 10, 10), 0.5);

    while (true) {
        menu();
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                shootingRange.addTarget(createTarget());
                break;
            case 2:
                shootingRange.simulate();
                break;
            case 3:
                shootingRange.printStatistics();
                break;
            case 4:
                shootingRange.generateRandomTargets();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Invalid choice" << std::endl;
        }
    }

    return 0;

}