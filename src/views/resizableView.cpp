#include "views/resizableView.hpp"

namespace views
{
    ResizableView::ResizableView(Position pos, Size s) : View(pos, s)
    {
    }

    void ResizableView::recenterWindow(Size screen)
    {
        int newRiga = (screen.riga - winSize.riga) / 2;
        int newColonna = (screen.colonna - winSize.colonna) / 2;
        mvwin(window, newRiga, newColonna);
    }

    void ResizableView::handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView)
    {
        if (changedView)
        {
            if (screen.getCurrent() < winSize)
            {
                handleScreenToSmall();
            }
            else
            {
                recenterWindow(screen.getCurrent());
            }
        }
    }

    void ResizableView::handleScreenToSmall() {}

    void ResizableView::render(bool forces){
        View::render(forces);
    }

}; // namespace views
