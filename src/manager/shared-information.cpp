#include "manager/shared-information.hpp"


namespace manager {
    
        SharedInformation &SharedInformation::getInstance() {
            static SharedInformation instance;
            return instance;
        }
    
        SharedInformation::SharedInformation() {
            lastPlayerScore = 0;
        }
    
        SharedInformation::~SharedInformation() {}
    
        int SharedInformation::getLastPlayerScore() {
            return lastPlayerScore;
        }
    
        void SharedInformation::setLastPlayerScore(int score) {
            lastPlayerScore = score;
        }
};  // namespace manager