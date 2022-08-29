#include "views/menu-view.hpp"

#include <cstring>

namespace views {
    MenuView::MenuView()
        : ResizableView({0, 0}, manager::kMenuSize), name_("MenuView") {}

    // fa il override di questa funzione da view
    bool MenuView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
        if (ResizableView::handleScreenBeforeRender(screen, view, changedView))
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
    // fa il override di questa funzione da view
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

    // fa il override di questa funzione da view
    void MenuView::render(bool force) {
        if (force) {
            View::clearWindow();
            printMenu_();
            char start[] = "Premere <Space> per incominciare";
            mvwprintw(window, 6, (manager::kMenuSize.colonna - strlen(start)) / 2, start);
            char quit[] = "Premere <Q> per abbandonare";
            mvwprintw(window, 8, (manager::kMenuSize.colonna - strlen(quit)) / 2, quit);
        }
        ResizableView::render(false);
    }

    void MenuView::handleScreenToSmall(manager::ViewManager *manager) {
        ScreenTooSmallView *toSmall = new ScreenTooSmallView(manager::kMenuSize);
        manager->pushView(toSmall);
    }

    const char *MenuView::getName() {
        return name_;
    }

};  // namespace views