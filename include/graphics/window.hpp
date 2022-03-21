#pragma once
#include <ncurses.h>
#include "size.hpp"

namespace graphics{
    class Window{
        Window(Size size);

        ~Window();

    private:
        Size size;
    };
};