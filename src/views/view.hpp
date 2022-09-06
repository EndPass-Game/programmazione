#pragma once

#include <ncurses.h>

#include "gamestruct/position.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/state-watcher.tpp"
#include "manager/view-manager.fwd.h"  // forward declaration, circular dependency

namespace views {
    /// @brief classe base che astrae la visualizzazione di una schemata
    class View {
      protected:
        WINDOW *window;
        Size winSize;
        Position winPosition;
        const char *name_;

      public:
        View(Position pos, Size size);

        View(Position pos, Size size, const char *name);

        virtual ~View();

        /**
         * @brief viene chiamata prima del render, modifica
         * la view manager a seconda delle necessità
         *
         * @return returna se devi fare un force update dello schermo oppure no
         */
        virtual bool handleScreenBeforeRender(
            StateWatcher<Size> &screen,
            manager::ViewManager *view,
            bool changedView
        ) = 0;

        /**
         * @brief funzione astratta: ogni classe figlia avrà una propria funzione
         * per gestire gli input, che possono essere diverse ad ogni view.
         *
         * @param input dato dall'InputManager
         */
        virtual void handleInput(char input) = 0;

        /**
         * @brief la funzione che viene chiamata per aggiornare lo schermo e il forces obbliga a riprintare
         */
        virtual void render(bool forces);

        void clearWindow();

        virtual const char *getName();
    };
};  // namespace views