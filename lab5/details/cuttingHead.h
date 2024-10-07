class CuttingHead : public Detail {
    public:
        CuttingHead(int replacePrice, int repairPrice, int repairTime, int nominalLifetime) : Detail(replacePrice, repairPrice, repairTime, nominalLifetime) {}
        int work(int intense) override {
            if (!needToReplace()) {
                currentLifetime += 10 * intense;
                return 0;
            } else {
                return repairTime;
            }
        }
        bool needToReplace() override {
            return currentLifetime >= nominalLifetime;
        }
};