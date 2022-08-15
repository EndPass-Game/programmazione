#include "views/pause-view.hpp"

// TODO(gio): fixa gli include di questo file, segui la filosofia: "includi quello che usi"
// https://google.github.io/styleguide/cppguide.html#Include_What_You_Use

namespace views {

    PauseView::PauseView(Position pos)
        : ResizableView(pos, manager::kGameWindowsSize), name_("PauseView") {}

    bool PauseView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
        if (ResizableView::handleScreenBeforeRender(screen, view, changedView))
            return true;
        if (quit) {
            view->clear();
        } else if (returnToGame) {
            view->popView();
        }
        return false;
    }

    void PauseView::handleInput(char input) {
        switch (input) {
            case ' ':
                returnToGame = true;
                break;
            case 'q':
            case 'Q':
                quit = true;
                break;
        }
    }

    void PauseView::render(bool force) {
        char pausa[] = "PAUSA";
        mvwprintw(window, (manager::kGameWindowsSize.riga) / 2 - 3, (manager::kGameWindowsSize.colonna - strlen(pausa)) / 2, pausa);
        char riprendere[] = "Premere la <Space> per riprendere.";
        mvwprintw(window, (manager::kGameWindowsSize.riga) / 2, (manager::kGameWindowsSize.colonna - strlen(riprendere)) / 2, riprendere);
        char uscire[] = "<Q> per uscire";
        mvwprintw(window, (manager::kGameWindowsSize.riga) / 2 + 2, (manager::kGameWindowsSize.colonna - strlen(uscire)) / 2, uscire);
        ResizableView::render(force);
    }

    void PauseView::handleScreenToSmall(manager::ViewManager *manager) {
        ScreenTooSmallView *screenToSmall = new ScreenTooSmallView(manager::kGameWindowsSize);
        manager->pushView(screenToSmall);
    }

    const char *PauseView::getName() {
        return name_;
    }

};  // namespace views