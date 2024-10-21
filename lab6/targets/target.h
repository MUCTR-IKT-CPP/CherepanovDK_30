class Target {
    protected:
        int distance;
        int size;
        int health;
        bool destroyed = false;
        int destructionRound;

    public:
        
        Target(int distance, int size, int health) : distance(distance), size(size), health(health) {}

        int getDistance() const { return distance; }

        int getSize() const { return size; }

        int getHealth() const { return health; }

        void reduceHealth(int damage) {
            health -= damage;
        }

        bool isAlive() const {
            return health > 0;
        }

        void destroy() {
            destroyed = true;
        }

        void setDestructionRound(int round) {
            destructionRound = round;
        }


        virtual double getHitDifficulty() const = 0;

        virtual void print(std::ostream& os) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const Target& target) {
            target.print(os);
            return os;
        }
};