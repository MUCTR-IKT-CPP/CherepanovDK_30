class StandardTarget : public Target {
    public:
        StandardTarget(int distance, int size, int health) : Target(distance, size, health) {}

        /**
         * Calculates the hit difficulty of the target. The difficulty is a value from 0 to 1, where 1 is the easiest to hit and 0 is the most difficult.
         * The difficulty is calculated as 1 - (target size / distance) and then some randomness is added to it.
         * The difficulty is then clamped to the range 0 to 1.
         * @return the hit difficulty of the target
         */
        double getHitDifficulty() const override {
            double difficulty = 1.0 - (static_cast<double>(size) / distance);

            double randomness = (static_cast<double>(std::rand()) / RAND_MAX) * 0.2 - 0.1;
            difficulty += randomness;
            if (difficulty < 0.0) difficulty = 0.0;
            if (difficulty > 1.0) difficulty = 1.0;
            return difficulty;
        }


        /**
         * Prints the details of the standard target to the provided output stream.
         * If the target is not destroyed, prints its distance, size, and health.
         * If the target is destroyed, prints the round in which it was destroyed.
         * @param os the output stream to print the target details to
         */
        void print(std::ostream& os) const {
            if (!destroyed) {
                os << "StandardTarget: " << "Distance: " << distance << ", Size: " << size << ", Health: " << health;
            } else {
                os << "Standard Target: " << "Destroyed at round: " << destructionRound;
            }
        }
};   
