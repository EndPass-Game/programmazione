#include "views/menu-view.hpp"

#include <cstring>

namespace views {
    MenuView::MenuView()
        : StaticTextView({0, 0}, manager::kMenuSize, "MenuView") {}

    bool MenuView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
        if (StaticTextView::handleScreenBeforeRender(screen, view, changedView))
            return true;
        if (quit_) {
            view->clear();
        } else if (start_) {
            GameView *game = new GameView({0, 0});
            view->pushView(game);
            start_ = false;
        }
        return false;
    }

    void MenuView::handleInput(char input) {
        switch (input) {
            case 'q':
            case 'Q':
                quit_ = true;
                break;
            case ' ':
                start_ = true;
                break;
        }
    }

    void MenuView::printMenu_() {
        for (int riga = 0; riga < kAsciiArtAltezza_; riga++) {
            mvwprintw(window, riga + 1, (manager::kMenuSize.colonna - strlen(kAsciiArt_[riga])) / 2, kAsciiArt_[riga]);
        }
    }

    void MenuView::printText() {
        printMenu_();
        char start[] = "Premere <Space> per incominciare";
        mvwprintw(window, 6, (manager::kMenuSize.colonna - strlen(start)) / 2, start);
        char quit[] = "Premere <Q> per abbandonare";
        mvwprintw(window, 8, (manager::kMenuSize.colonna - strlen(quit)) / 2, quit);
    }

};  // namespace views