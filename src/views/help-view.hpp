
#pragma once

#include <cstring>

#include "manager/view-manager.hpp"
#include "views/resizable-view.hpp"
#include "views/screen-too-small.hpp"

namespace views {
    class HelpView : public ResizableView {
      private:
        bool quit = false;
        bool returnToGame = false;
        const char *name_ = "Pause";

      public:
        HelpView(Position pos);

        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) override;

        void handleInput(char input) override;

        void render(bool force) override;

        void handleScreenToSmall(manager::ViewManager *manager) override;

        const char *getName() override;
    };
};  // namespace views