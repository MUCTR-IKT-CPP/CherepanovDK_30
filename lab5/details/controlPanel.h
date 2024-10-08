class ControlPanel : public Detail {
    private:
        int lifeTimeRatio = 5;
    public:
        ControlPanel(int replacePrice, int repairPrice, int repairTime, int nominalLifetime) : Detail(replacePrice, repairPrice, repairTime, nominalLifetime) {}

        /**
         * Simulates the work of the detail and returns the time in hours that the detail was idle.
         *
         * If the detail is not broken, increases the current lifetime by lifeTimeRatio + lifeTimeRatio * intense - 20.
         * If the detail is broken, returns the repair time.
         *
         * @param intense the intensity of the work
         * @return the time in hours that the detail was idle
         */
        int work(int intense) override {
            if (!needToReplace()) {
                currentLifetime += lifeTimeRatio + lifeTimeRatio * intense - 20;
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