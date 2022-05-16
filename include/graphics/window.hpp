#pragma once
#include <ncurses.h>
#include "size.hpp"
#include "position.hpp"

namespace graphics
{
    class Window
    {
    public:
        Window(Position pos,Size size);

        ~Window();

        WINDOW* getWindow();
        void moveWindow(Position pos);
        Size  getSize();

    private:
        Position position_;
        Size size_;
        WINDOW* win_;
    };
};