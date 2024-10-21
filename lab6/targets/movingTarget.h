class MovingTarget : public Target {
    protected:
        int speed;

    public:
        MovingTarget(int distance, int size, int health, int speed) : Target(distance, size, health), speed(speed) {}


        double getHitDifficulty() const override {


            double difficulty = 1.0 - (static_cast<double>(size) / (distance * (1 + 0.5 * speed)));
            
            double randomness = (static_cast<double>(std::rand()) / RAND_MAX) * 0.2 - 0.1;
            difficulty += randomness;

            if (difficulty < 0.0) difficulty = 0.0;
            if (difficulty > 1.0) difficulty = 1.0;
            return difficulty;
        }

        void print(std::ostream& os) const {
            if (!destroyed) {
            os << "MovingTarget: " << "Distance: " << distance << ", Size: " << size << ", Health: " << health << ", Speed: " << speed;
            } else {
                os << "Moving Target: " << "Destroyed at round: " << destructionRound;
            }
        }

};