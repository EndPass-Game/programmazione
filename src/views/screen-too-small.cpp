#include "views/screen-too-small.hpp"


namespace views {

    ScreenTooSmallView::ScreenTooSmallView(Size minScreen)
        : View({0, 0}, {0, 0},"ScreenTooSmallView") ,
          minimumRequired_(minScreen)
          {}

    void ScreenTooSmallView::handleInput(char input) {
        if (input == 'q') {
            quit_ = true;
        }
    }
    void ScreenTooSmallView::render(bool force) {
        mvwprintw(window, 0, 0, "Schermo troppo piccolo");
        View::render(force);
    }

    bool ScreenTooSmallView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
        if (screen.getCurrent().colonna >= minimumRequired_.colonna and screen.getCurrent().riga >= minimumRequired_.riga) {
            view->popView();
            return true;
        }
        if (quit_) {
            view->clear();
            return true;
        }
        return false;
    }

};  // namespace views
