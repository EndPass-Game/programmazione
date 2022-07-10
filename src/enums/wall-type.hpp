#pragma once

namespace enums {
    // Tipologie di Wall esistenti
    // saranno usate per generare i muri
    enum class WallType {
        VERT = '|',
        HORIZ = '-',
        ANGLE = '+',
        DOORCLOSED = 'X',
        DOOROPEN = 'O',
        EMPTY = ' ',
        DEFAULT = 'D' // default for displayble segment
    };
}; // namespace enums