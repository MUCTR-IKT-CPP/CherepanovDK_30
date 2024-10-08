class Motor : public Detail {
    private:
        int lifeTimeRatio = 15;
    public:
        Motor(int replacePrice, int repairPrice, int repairTime, int nominalLifetime) : Detail(replacePrice, repairPrice, repairTime, nominalLifetime) {}
        int work(int intense) override {
            if (needToReplace() == 0) {
                currentLifetime += lifeTimeRatio + lifeTimeRatio * intense - 2;
                return 0;
            } else {
                return repairTime;
            }
        }
        bool needToReplace() override {
            return currentLifetime >= nominalLifetime;
        }
};