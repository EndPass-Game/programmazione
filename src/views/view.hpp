#pragma once

#include <ncurses.h>

#include "gamestruct/position.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/state-watcher.hpp"
#include "manager/view-manager.fwd.h"  // forward declaration, circular dependency

namespace views {
    // classe base che astrae la visualizzazione di una schemata
    class View {
      protected:
        WINDOW *window;
        Size winSize;
        Position winPosition;
        const char *name_ = "View";

      public:
        // viene chiamata prima del render, modifica la view manager a seconda delle
        // necessità
        virtual bool handleScreenBeforeRender(
            StateWatcher<Size> &screen,
            manager::ViewManager *view,
            bool changedView
        ) = 0;

        // funzione astratta: ogni classe figlia avrà una propria funzione
        // per gestire gli input, che possono essere diverse ad ogni view.
        virtual void handleInput(char input) = 0;

        // la funzione che viene chiamata per aggiornare lo schermo e il forces obbliga a riprintare
        virtual void render(bool forces);

        // create the windows
        View(Position pos, Size size);
        // delete the window
        virtual ~View();

        virtual const char *getName();
    };
};  // namespace views