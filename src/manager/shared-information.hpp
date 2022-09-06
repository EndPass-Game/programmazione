#pragma once

namespace manager {
    /**
     * @brief Questa class è un singoletto che agisce da provider
     * per alcune informazioni utilizzate
     * da più files difficilemente collegabili tra loro
     */
    class SharedInformation {
      private:
        int lastPlayerScore;

      public:
        /// @returns l'istanza singleton
        static SharedInformation &getInstance();

        SharedInformation();

        SharedInformation(const SharedInformation &other) = delete;

        SharedInformation &operator=(const SharedInformation &other) = delete;

        ~SharedInformation();

        int getLastPlayerScore();

        void setLastPlayerScore(int score);
    };
};  // namespace manager
