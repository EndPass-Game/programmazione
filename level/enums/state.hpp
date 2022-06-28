#pragma once

namespace level {
    namespace enums {
        // elenca tutte le tipologie stato per una cella delle collisioni
        enum State {
            EMPTY = 0,
            WALL = 1,
            ENTRYDOOR = 2,
            EXITDOOR = 3,
            PLAYER = 4,
            ENEMY = 5,
            BULLET = 6,
        };
    }; // namespace enums 
}; // namespace level 