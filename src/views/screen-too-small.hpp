#pragma once

#include "gamestruct/state-watcher.hpp"
#include "manager/view-manager.hpp"
#include "views/view.hpp"

namespace views {
    // view che viene chiamata quando la schermata è troppo piccola
    class ScreenTooSmallView : public View {
      private:
        // dimensioni minime richieste per la finestra
        Size minimumRequired_;
        bool quit_ = false;

      public:
        ScreenTooSmallView(Size minimumRequired_);

        void handleInput(char input);

        void render(bool force);

        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView);
    };
};  // namespace views
