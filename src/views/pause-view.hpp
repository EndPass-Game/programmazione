#pragma once

#include <cstring>

#include "manager/view-manager.hpp"
#include "views/static-text-view.hpp"

namespace views {
    /**
     * @brief classe che mostra la schermata di pausa del gioco
     */
    class PauseView : public StaticTextView {
      private:
        bool quit = false;
        bool returnToGame = false;

      public:
        PauseView();

        bool handleScreenBeforeRender(
            StateWatcher<Size> &screen,
            manager::ViewManager *view,
            bool changedView
        ) override;

        void handleInput(char input) override;

        void printText() override;
    };
};  // namespace views