class CuttingHead : public Detail {
    private:
        int lifeTimeRatio = 30;
    public:
        CuttingHead(int replacePrice, int repairPrice, int repairTime, int nominalLifetime) : Detail(replacePrice, repairPrice, repairTime, nominalLifetime) {}
        
        /**
         * Simulates the work of the detail and returns the time in hours that the detail was idle.
         *
         * If the detail is not broken, increases the current lifetime by lifeTimeRatio + 2 * lifeTimeRatio * intense.
         * If the detail is broken, returns the repair time.
         *
         * @param intense the intensity of the work
         * @return the time in hours that the detail was idle
         */
        int work(int intense) override {
            if (!needToReplace()) {
                currentLifetime += lifeTimeRatio + 2 * lifeTimeRatio * intense;
                return 0;
            } else {
                return repairTime;
            }
        }
        
        /**
         * Checks if the detail needs to be replaced.
         *
         * @return true if the detail needs to be replaced, false otherwise
         */
        bool needToReplace() override {
            return currentLifetime >= nominalLifetime;
        }
};