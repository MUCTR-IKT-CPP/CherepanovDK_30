class StandardTarget : public Target {
    public:
        StandardTarget(int distance, int size, int health) : Target(distance, size, health) {}

        double getHitDifficulty() const override {
            double difficulty = 1.0 - (static_cast<double>(size) / distance);

            double randomness = (static_cast<double>(std::rand()) / RAND_MAX) * 0.2 - 0.1;
            difficulty += randomness;
            if (difficulty < 0.0) difficulty = 0.0;
            if (difficulty > 1.0) difficulty = 1.0;
            std::cout << "Standard target difficulty: " << difficulty << std::endl;
            return difficulty;
        }


        void print(std::ostream& os) const {
            os << "StandardTarget: " << "Distance: " << distance << ", Size: " << size << ", Health: " << health;
        }
};   
