#pragma once

#include <ncurses.h>

#include "gamestruct/state-watcher.hpp"
#include "manager/view-manager.hpp"
#include "views/view.hpp"

namespace views {
    class ResizableView : public View {
      protected:
        // ricentra la finestra se la dimensione dello schermo cambia
        void recenterWindow(Size screen);
        const char *name_ = "ResizableView";

      public:
        // override di quella di view
        // se la scherma è contenuta nella attuale fa il recenter
        // se no chiama handle screen to small
        virtual bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *viewManager, bool changedView);

        ResizableView(Position pos, Size s);

        virtual void handleScreenToSmall(manager::ViewManager *manager) = 0;

        virtual void render(bool force);

        virtual const char *getName();
    };
};  // namespace views