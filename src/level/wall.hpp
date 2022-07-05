#pragma once 

#include "gamestruct/displayable.hpp"

// tutti i muri dovranno essere mostrati e displayable implementa questa funzionalità
namespace level {
    using Wall = Displayable;
}; // namespace level