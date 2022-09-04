#pragma once

namespace manager {
    class SharedInformation {
      private:
        int lastPlayerScore;

      public:
        // @returns l'istanza singleton
        static SharedInformation &getInstance();

        SharedInformation();

        SharedInformation(const SharedInformation &other) = delete;
        SharedInformation &operator=(const SharedInformation &other) = delete;

        ~SharedInformation();

        int getLastPlayerScore();
        void setLastPlayerScore(int score);
    };
};  // namespace manager