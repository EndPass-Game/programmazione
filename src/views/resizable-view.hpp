#pragma once

#include <ncurses.h>

#include "gamestruct/state-watcher.tpp"
#include "manager/view-manager.hpp"
#include "views/view.hpp"

namespace views {

    /// @brief classe astratta che recentra la finestra automaticamente
    class ResizableView : public View {
      protected:
        /// @brief ricentra la finestra se la dimensione dello schermo cambia
        void recenterWindow(Size screen);

      public:
        ResizableView(Position pos, Size s);

        ResizableView(Position pos, Size s, const char *name);

        /**
         * @brief se la scherma è contenuta nella attuale fa il recenter
         * se no chiama handle screen to small
         */
        virtual bool handleScreenBeforeRender(
            StateWatcher<Size> &screen,
            manager::ViewManager *viewManager,
            bool changedView
        ) override;

        virtual void handleScreenToSmall(manager::ViewManager *manager) = 0;

        virtual void render(bool force);
    };
};  // namespace views