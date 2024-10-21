#include "include.h"
#include <memory>

int main() {

    std::srand(std::time(0));

    ShootingRange shootingRange(std::make_shared<Gun>(30, 3, 10, 10), 0.5);

    shootingRange.generateRandomTargets();
    shootingRange.simulate();
    std::cout << shootingRange << std::endl;

    return 0;

}