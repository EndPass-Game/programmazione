#pragma once

#include <ncurses.h>
#include "views/view.hpp"

namespace views
{
    class ResizableView : public View
    {
    private:

        Position recenterWindow(Size screen);

    public:


        virtual void handleScreenBeforeRender(Changeable<Size> &screen,manager::ViewManager * viewManager);

        ResizableView(Position pos,Size s);

        virtual void handleScreenToSmall();

    };
}; // namespace views