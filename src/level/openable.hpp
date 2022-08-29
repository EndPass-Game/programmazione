#pragma once

namespace level {
    /// Questa classe rappresenta in modo astratto qualcosa che si può aprire
    /// e chiudere.
    class Openable {
      private:
        /// variabile incapsulata per indicare lo stato dell'apertura
        bool isOpen_;

      public:
        Openable(bool isOpen);
        virtual ~Openable() = default;
        bool isOpen() const;
        virtual void open();
        virtual void close();
    };
}  // namespace level
