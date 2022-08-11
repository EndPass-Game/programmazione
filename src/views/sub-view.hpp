#pragma once
#include <ncurses.h>

#include "gamestruct/position.hpp"
#include "gamestruct/size.hpp"

namespace views {
    class SubView {
      protected:
        WINDOW *subWin_;

      public:
        SubView(WINDOW *win, Size size, Position pos);
        virtual ~SubView();

        virtual void render(bool force);
    };
};  // namespace views