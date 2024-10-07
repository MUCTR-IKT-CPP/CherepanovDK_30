#include "include.h"


int main() {
    Machine machine;
    machine.addDetail(std::make_shared<Motor>(100, 10, 10, 100));
    machine.addDetail(std::make_shared<Shaft>(100, 10, 10, 100));
    machine.work(12, 1);
    std::cout << machine << std::endl;

    return 0;

}