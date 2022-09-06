#pragma once

#include "gamestruct/state-watcher.tpp"
#include "manager/view-manager.hpp"
#include "views/view.hpp"

namespace views {
    /**
     * @brief View che viene chiamata quando lo schermo è
     * troppo piccolo per renderizzare la schermata che
     * si dovrebbe visualizzare
     */
    class ScreenTooSmallView : public View {
      private:
        // dimensioni minime richieste per la finestra
        Size minimumRequired_;
        bool quit_ = false;

      public:
        ScreenTooSmallView(Size minimumRequired_);

        void handleInput(char input) override;

        void render(bool force) override;

        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) override;
    };
};  // namespace views
