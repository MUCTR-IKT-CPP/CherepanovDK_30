class ControlPanel : public Detail {
    private:
        int lifeTimeRatio = 5;
    public:
        ControlPanel(int replacePrice, int repairPrice, int repairTime, int nominalLifetime) : Detail(replacePrice, repairPrice, repairTime, nominalLifetime) {}

        int work(int intense) override {
            if (!needToReplace()) {
                currentLifetime += lifeTimeRatio + lifeTimeRatio * intense - 20;
                return 0;
            } else {
                return repairTime;
            }
        }

        bool needToReplace() override {
            return currentLifetime >= nominalLifetime;
        }
};