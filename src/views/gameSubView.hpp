#pragma once 

#include "views/subView.hpp"
#include "manager/viewManager.hpp"
#include "manager/level.hpp"


namespace views {
    class GameSubView:SubView{
    protected:
        manager::Level *levelManager_;
    public:
        GameSubView(WINDOW * win);
        void render(bool force);
        void handleInput(char input);
    };
}; // namespace views