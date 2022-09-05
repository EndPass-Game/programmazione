#pragma once

#include <ncurses.h>

#include "gamestruct/state-watcher.tpp"
#include "manager/view-manager.hpp"
#include "views/resizable-view.hpp"
#include "views/screen-too-small.hpp"

namespace views {
    /**
     * @brief astrazione di una view che printa solo il testo e che non cambia
     */
    class StaticTextView : public ResizableView {
      public:
        StaticTextView(Position pos, Size s);

        StaticTextView(Position pos, Size s, const char *name);

        /**
         * @brief funzione che printa il testo statico
         */
        virtual void printText() = 0;

        virtual bool handleScreenBeforeRender(
            StateWatcher<Size> &screen,
            manager::ViewManager *viewManager,
            bool changedView
        ) override;

        /// @brief tutte queste schermate quando diventano troppo piccole chiamano screen to small
        void handleScreenToSmall(manager::ViewManager *manager);

        /// @brief questa funzione viene implementata e chiama printText
        void render(bool force);
    };
};  // namespace views
