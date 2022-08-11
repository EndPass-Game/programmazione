#pragma once

#include <ncurses.h>

#include "manager/level.hpp"
#include "manager/view-manager.hpp"
#include "views/sub-view.hpp"

namespace views {
    class GameSubView : public SubView {
      protected:
        manager::Level *levelManager_;

      public:
        GameSubView(WINDOW *win, manager::Level *levelManager);
        void render(bool force);
        void handleInput(char input);
    };
};  // namespace views