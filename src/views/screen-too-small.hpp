#pragma once
#include "views/view.hpp"
#include "gamestruct/state-watcher.hpp"
#include "manager/view-manager.hpp"

namespace views {
    class ScreenTooSmallView: public View {
    private:
        Size minimumRequired_; // dimensioni minime richieste per la finestra
        bool quit_ = false;
    public:

        ScreenTooSmallView(Size minimumRequired_);

        void handleInput(char input);

        void render(bool force);

        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view,bool changedView);
    };
}; // namespace views
