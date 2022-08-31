#pragma once

#include <ncurses.h>

#include "gamestruct/state-watcher.hpp"
#include "manager/view-manager.hpp"
#include "views/resizable-view.hpp"
#include "views/screen-too-small.hpp"

namespace views {

    // astrazione di una view che printa solo il testo e che non cambia

    class StaticTextView : public ResizableView {
      public:
        // funzione che printa il testo statico
        virtual void printText() = 0;

        virtual bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *viewManager, bool changedView);

        StaticTextView(Position pos, Size s);

        StaticTextView(Position pos, Size s, const char *name);

        // tutte queste schermate quando diventano troppo piccole chiamano screen to small
        void handleScreenToSmall(manager::ViewManager *manager);

        // questa funzione viene implementata e chiama printText
        void render(bool force);
    };
};  // namespace views