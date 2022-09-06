#pragma once

namespace level {
    /**
     * @brief Questa classe rappresenta in modo astratto qualcosa che si può aprire
     * e chiudere.
     */
    class Openable {
      private:
        /// variabile incapsulata per indicare lo stato dell'apertura
        bool isOpen_;

      public:
        /**
         * @brief Costruttore di un oggetto Openable
         *
         * @param isOpen lo stato dell'apertura
         */
        Openable(bool isOpen);

        /**
         * @brief Distruttore generato dal compilatore
         */
        virtual ~Openable() = default;

        bool isOpen() const;

        virtual void open();

        virtual void close();
    };
}  // namespace level
