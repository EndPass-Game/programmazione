#pragma once

namespace enums {
    // Tipologie di Wall esistenti
    // saranno usate per generare i muri
    enum WallType {
        VERT = '|',
        HORIZ = '-',
        ANGLE = '+',
        DOORCLOSED = 'X',
        DOOROPEN = ' ',
        EMPTY = ' '
    };
}; // namespace enums