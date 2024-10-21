#include <ctime>


class Gun {
    protected:
        int magSize;
        int burstSize;
        int ammo;
        double correcction = 0.1;
        int damage;

    public:
        Gun(int magSize, int burstSize, int ammo, int damage) : magSize(magSize), burstSize(burstSize), ammo(ammo), damage(damage) {}

        int getMagSize() const { return magSize; }

        int singleShot(double difficulty) {
            if (ammo > 0) {
                ammo--;
            }
            if (chanceToHit() > difficulty) {
                return damage;
            } else {
                return 0;
            }
        }   

        int burstShot(double difficulty) {
            int currentDamage = 0;
            if (ammo >= burstSize) {
                ammo -= burstSize;
                currentDamage = damage * burstSize;
            } else {
                currentDamage = damage * ammo;
                ammo = 0;

            }

            if ( (chanceToHit() - correcction) > difficulty) {
                return currentDamage;
            } else {
                return 0;
            }
            
        }

        void reload() {
            if (ammo < magSize) {
                ammo = magSize;
            }
        }

        double chanceToHit() {
            return (double)rand() / RAND_MAX;
        }

        int getAmmo() const { return ammo; }

        int getDamage() const { return damage; }

        int getBurstSize() const { return burstSize; }

        double getBurstChance() {
            return (double)rand() / RAND_MAX;
        }
};   