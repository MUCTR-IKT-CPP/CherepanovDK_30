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

        /**
         * Simulates a single shot of the gun.
         * If the gun has ammo, decrements the ammo and then checks if the shot hits.
         * If the shot hits, returns the gun's damage.
         * If the shot misses, returns 0.
         * @param difficulty the difficulty of the target
         * @return the damage dealt by the shot
         */
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

        /**
        * Simulates a burst shot of the gun.
        * If the gun has enough ammo for a burst shot, calculates the damage dealt by the burst based on the current ammo and burst size.
        * Checks if the burst hits the target based on the difficulty and the gun's correction factor.
        * Returns the total damage dealt by the burst shot.
        * 
        * @param difficulty the difficulty of the target
        * @return the damage dealt by the burst shot
        */
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

        /**
         * Reloads the gun.
         * If the current ammo is less than the mag size, reloads the gun to the mag size.
         * Otherwise, does nothing.
         */
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