#pragma once
#include <ncurses.h>  // WINDOW

#include "manager/level.hpp"
#include "views/sub-view.hpp"

namespace views {
    class LogSubView : SubView {
      private:
        manager::Level *levelManager_;

      public:
        LogSubView(WINDOW *win, manager::Level *levelManager);

        void render(bool force);
    };
};  // namespace views