class Shaft : public Detail {
    private:
        int lifeTimeRatio = 10;
    public:
        Shaft(int replacePrice, int repairPrice, int repairTime, int nominalLifetime) : Detail(replacePrice, repairPrice, repairTime, nominalLifetime) {}
        int work(int intense) override {
            if (needToReplace() == 0) {
                currentLifetime += lifeTimeRatio + lifeTimeRatio * intense;
                return 0;
            } else {
                return repairTime;
            }
        }

        bool needToReplace() override {
            return currentLifetime >= nominalLifetime;
        }
};