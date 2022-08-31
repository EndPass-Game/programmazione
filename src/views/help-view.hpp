
#pragma once

#include <cstring>

#include "manager/view-manager.hpp"
#include "views/static-text-view.hpp"

namespace views {
    class HelpView : public StaticTextView {
      private:
        bool quit = false;
        bool returnToGame = false;

      public:
        HelpView(Position pos);

        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) override;

        void handleInput(char input) override;

        void printText() override;
    };
};  // namespace views