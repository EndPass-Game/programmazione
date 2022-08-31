#pragma once

namespace enums {
    /**
     * @brief Rappresenta il carattere di tutte le tipologie di muro
     * o porte printabili
     *
     */
    enum class WallType {
        VERT = '|',
        HORIZ = '-',
        ANGLE = '+',
        DOORCLOSED = 'X',
        DOOROPEN = 'O',
        EMPTY = ' ',
        DEFAULT = 'D'  // default for displayble segment
    };
};  // namespace enums
