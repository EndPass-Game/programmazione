#pragma once
#include "views/view.hpp"

namespace views
{
    class ScreenToSmallView: public View
    {
    private:

        Size minimumRequired_;
        bool quit_=false;
    public:

        ScreenToSmallView(Size minimumRequired_);

        void handleInput(char input);

        void render(bool force);

        bool handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView);

    };
}; // namespace views
