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

        /**
         * @brief getter di `isOpen_`
         */
        bool isOpen() const;

        /**
         * @brief Apre l'oggetto
         */
        virtual void open();

        /**
         * @brief Chiude l'oggetto
         */
        virtual void close();
    };
}  // namespace level
