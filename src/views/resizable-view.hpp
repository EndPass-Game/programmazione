#pragma once

#include <ncurses.h>

#include "views/view.hpp"

namespace views
{
    class ResizableView : public View
    {
    protected:
        //ricentra la finestra se la dimensione dello schermo cambia
        void recenterWindow(Size screen);

    public:
        // override di quella di view
        // se la scherma è contenuta nella attuale fa il recenter
        // se no chiama handle screen to small
        virtual bool handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *viewManager,bool changedView);

        ResizableView(Position pos, Size s);

        virtual void handleScreenToSmall(manager::ViewManager* manager);

        virtual void render(bool force);
    };
}; // namespace views