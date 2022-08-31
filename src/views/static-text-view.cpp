#include "views/static-text-view.hpp"

namespace  views{
    StaticTextView::StaticTextView(Position pos, Size s)
        : ResizableView(pos, s) {}
    
    StaticTextView::StaticTextView(Position pos, Size s, const char *name)
        : ResizableView(pos, s, name) {}
    
    
    bool StaticTextView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
        return ResizableView::handleScreenBeforeRender(screen, view, changedView);
    }
    
    void StaticTextView::render(bool force) {
        if(force){
            View::clearWindow();
            printText();
            ResizableView::render(false);
        }
    }
    
    void StaticTextView::handleScreenToSmall(manager::ViewManager *manager) {
        ScreenTooSmallView *screenToSmall = new ScreenTooSmallView(manager::kGameWindowsSize);
        manager->pushView(screenToSmall);
    }

}; // namespace views