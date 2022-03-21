#pragma once

#include "size.hpp"
#include "changeable.hpp"
#include <ncurses.h>

namespace graphics
{
    class ResizableWindow
    {
    protected:
        //mantiene una struttura che ricorda lo stato vecchio della size
        Changeable<Size> *currentScreenSize_;

    public:
        ResizableWindow();
        ~ResizableWindow();
        bool updateScreenSize();
        //esegue delle operazioni in base a come si è modificata la dimensione
        // setta lo stato Game to small e le varie schermate
        //bool  handleScreenSizeChange(Level* level);
        virtual void handleScreenSizeChange() {}
    };
} // namespace manager
