#pragma once 

#include <ncurses.h>

#include "views/sub-view.hpp"
#include "manager/view-manager.hpp"
#include "manager/level.hpp"

namespace views {
    class GameSubView: public SubView{
    protected:
        manager::Level *levelManager_;
    public:
        GameSubView(WINDOW * win);
        ~GameSubView();
        void render(bool force);
        void handleInput(char input);
    };
}; // namespace views