#pragma once

#include "ncurses.h"
#include "gamestruct/position.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/changeable.hpp"
#include "manager/viewManager.hpp"


namespace views
{

    class View
    {
    protected:
        
        WINDOW *window;
     
        Size winSize;
        
        Position winPosition;


    public:

        virtual void handleScreenBeforeRender(Changeable<Size> &screen,manager::ViewManager* view);

        virtual void handleInput(char input);

        virtual void render(bool repaint);

        View(Position pos, Size s);

        ~View();
    };
}; // namespace views