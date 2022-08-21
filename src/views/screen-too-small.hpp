#pragma once
#include "gamestruct/state-watcher.hpp"
#include "manager/view-manager.hpp"
#include "views/view.hpp"

namespace views {
    class ScreenTooSmallView : public View {
      private:
        Size minimumRequired_;  // dimensioni minime richieste per la finestra
        bool quit_ = false;
        const char *name_;

      public:
        ScreenTooSmallView(Size minimumRequired_);

        void handleInput(char input);

        void render(bool force);

        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView);

        const char *getName();
    };
};  // namespace views
