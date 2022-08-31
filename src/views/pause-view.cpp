#include "views/pause-view.hpp"

namespace views {

    PauseView::PauseView()
        : StaticTextView({0, 0}, manager::kGameWindowsSize,"PauseView") {}

    bool PauseView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
        if (StaticTextView::handleScreenBeforeRender(screen, view, changedView))
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

    void PauseView::printText() {
        char pausa[] = "PAUSA";
        mvwprintw(window, (manager::kGameWindowsSize.riga) / 2 - 3, (manager::kGameWindowsSize.colonna - strlen(pausa)) / 2, pausa);
        char riprendere[] = "Premere la <Space> per riprendere.";
        mvwprintw(window, (manager::kGameWindowsSize.riga) / 2, (manager::kGameWindowsSize.colonna - strlen(riprendere)) / 2, riprendere);
        char uscire[] = "<Q> per uscire";
        mvwprintw(window, (manager::kGameWindowsSize.riga) / 2 + 2, (manager::kGameWindowsSize.colonna - strlen(uscire)) / 2, uscire);
    }

};  // namespace views