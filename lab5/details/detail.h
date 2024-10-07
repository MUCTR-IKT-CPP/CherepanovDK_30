#include <iostream>

class Detail {
    protected:
        int replacePrice;
        int repairPrice;
        int repairTime;
        int nominalLifetime;
        int currentLifetime = 0;

    public:
        Detail(int replacePrice, int repairPrice, int repairTime, int nominalLifetime) :
            replacePrice(replacePrice),
            repairPrice(repairPrice),
            repairTime(repairTime),
            nominalLifetime(nominalLifetime)
        {};

        virtual int work(int intense) = 0;

        virtual bool needToReplace() = 0;

        int replace() {
            std::cout << "Detail " << typeid(*this).name() << " was replaced" << std::endl;
            currentLifetime = 0;
            return replacePrice;
        }

        int repair() {
            std::cout << "Detail " << typeid(*this).name() << " was repaired" << std::endl;
            currentLifetime = currentLifetime * 0.8;
            return repairPrice;
        }

        int getRepairTime() {
            return repairTime;
        }

        friend std::ostream& operator<<(std::ostream& out, const Detail& detail) {
            out << "DetailClass: " << typeid(detail).name() << " | object data: "  <<" replace price:"  << detail.replacePrice 
            << " repair price: " << detail.repairPrice << " repair time: " << detail.repairTime 
            << " nominal lifetime: " << detail.nominalLifetime << " current lifetime: " << detail.currentLifetime << std::endl;
            return out;
        }
};