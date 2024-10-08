class CuttingHead : public Detail {
    private:
        int lifeTimeRatio = 30;
    public:
        CuttingHead(int replacePrice, int repairPrice, int repairTime, int nominalLifetime) : Detail(replacePrice, repairPrice, repairTime, nominalLifetime) {}
        int work(int intense) override {
            if (!needToReplace()) {
                currentLifetime += lifeTimeRatio + 2 * lifeTimeRatio * intense;
                return 0;
            } else {
                return repairTime;
            }
        }
        bool needToReplace() override {
            return currentLifetime >= nominalLifetime;
        }
};