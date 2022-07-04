#pragma once 
#include "views/subView.hpp"

namespace views {
    class ItemSubView:SubView{
    public:
        ItemSubView(WINDOW * win);

        void render(bool force);
    };
}; // namespace views