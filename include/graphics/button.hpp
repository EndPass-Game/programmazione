#pragma once
#include "window.hpp"
#include "changeable.hpp"
#include "string.h"
#include <ncurses.h>

namespace graphics
{
    class Button : public Window
    {
        Button(Size size, Position pos, char *name);

        void render(bool force);
        void setHover(bool isHover);
        bool isHover();
        ~Button();

    private:
        char *title;
        Changeable<bool> *hover;
    };
};