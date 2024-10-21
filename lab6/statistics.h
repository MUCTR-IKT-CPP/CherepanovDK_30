class Statistics {
    private:
        int round = 0;
        int totalDamage = 0;
        int totalShots = 0;
        int totalHits = 0;
        int destroyedTargets = 0;
        double avgDamage = 0.0;

    public:
        Statistics(int round, int totalDamage, int totalShots, int totalHits, int destroyedTargets, double avgDamage) {
            this->round = round;
            this->totalDamage = totalDamage;
            this->totalShots = totalShots;
            this->totalHits = totalHits;
            this->destroyedTargets = destroyedTargets;
            this->avgDamage = avgDamage;
        }

        friend std::ostream& operator<<(std::ostream& os, const Statistics& statistics) {
            os << "Round: " << statistics.round << " | total damage: " 
            << statistics.totalDamage << " | total shots: " << statistics.totalShots 
            << " | total hits: " << statistics.totalHits << " | destroyed targets: " 
            << statistics.destroyedTargets << " | avg damage: " << statistics.avgDamage;
            return os;
        }


};