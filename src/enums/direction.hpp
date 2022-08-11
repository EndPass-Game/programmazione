#pragma once

namespace enums {

    // Enumerator utilizzato principalmente per la direzione del movimento
    // 5 stati:
    // NONE = 0
    // UP = 1
    // DOWN = 2
    // LEFT = 3
    // RIGHT = 4
    // a cui sono associati dei valori numerici in caso di necessità di conversione
    enum class Direction {
        NONE = 0,
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4
    };
}  // namespace enums