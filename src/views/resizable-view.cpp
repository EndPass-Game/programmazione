#include "views/resizable-view.hpp"

namespace views {
    ResizableView::ResizableView(Position pos, Size s, const char *name)
        : View(pos, s, name) {}

    ResizableView::ResizableView(Position pos, Size s)
        : ResizableView(pos, s, "ResizableView") {
    }

    void ResizableView::recenterWindow(Size screen) {
        int newRiga = (screen.riga - winSize.riga) / 2;
        int newColonna = (screen.colonna - winSize.colonna) / 2;
        mvwin(window, newRiga, newColonna);
    }

    bool ResizableView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
        if (changedView) {
            if (screen.getCurrent().colonna < winSize.colonna or screen.getCurrent().riga < winSize.riga) {
                handleScreenToSmall(view);
                return true;
            } else {
                recenterWindow(screen.getCurrent());
            }
        }
        return false;
    }

    void ResizableView::render(bool forces) {
        View::render(forces);
    }

};  // namespace views
