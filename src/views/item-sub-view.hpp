#pragma once 
#include "views/sub-view.hpp"
#include "manager/level.hpp"
#include <ncurses.h> // WINDOW

namespace views {
    class ItemSubView:SubView{
    private:
        manager::Level *levelManager_;
    public:
        ItemSubView(WINDOW * win,manager::Level *levelManager);

        void render(bool force);
    };
}; // namespace views