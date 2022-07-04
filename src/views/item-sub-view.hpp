#pragma once 
#include "views/sub-view.hpp"

namespace views {
    class ItemSubView:SubView{
    public:
        ItemSubView(WINDOW * win);

        void render(bool force);
    };
}; // namespace views