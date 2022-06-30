#pragma once

#include "ncurses.h"
#include "gamestruct/position.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/changeable.hpp"

namespace views
{
    class View;
};

#include "manager/viewManager.hpp"

namespace views
{

    // classe base che astrae la visualizzazione di una schemata
    class View
    {
    protected:
        WINDOW *window;
        Size winSize;
        Position winPosition;

    public:
        // viene chiamata prima del rendere e questa è la funzione che può modificare la view manager
        virtual bool handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView);
        // gestisce gli input
        virtual void handleInput(char input);
        //la funzione che viene chiamata per aggiornare lo schermo e il forces obbliga a riprintare
        virtual void render(bool forces);
        //create the windows
        View(Position pos, Size size);
        //delete the window
        virtual ~View();
    };
}; // namespace views