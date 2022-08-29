#include "level/openable.hpp"

namespace level {
    Openable::Openable(bool isOpen)
        : isOpen_(isOpen) {}

    bool Openable::isOpen() const {
        return isOpen_;
    }

    void Openable::open() {
        isOpen_ = true;
    }

    void Openable::close() {
        isOpen_ = false;
    }
}  // namespace level
