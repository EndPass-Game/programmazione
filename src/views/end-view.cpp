#include "views/end-view.hpp"

#include <cstring>

namespace views {
    EndView::EndView()
        : ResizableView({0, 0}, manager::kMenuSize), name_("EndView") {}

    // fa il override di questa funzione da view
    bool EndView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
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
    void EndView::handleInput(char input) {
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

    void EndView::printMenu_() {
        for (int riga = 0; riga < kAsciiArtAltezza_; riga++) {
            mvwprintw(window, riga + 1, (manager::kMenuSize.colonna - strlen(kAsciiArt_[riga])) / 2, kAsciiArt_[riga]);
        }
    }

    // fa il override di questa funzione da view
    void EndView::render(bool force) {
        if (force) {
            View::clearWindow();
            printMenu_();
            char start[] = "Premere <Space> per tornare al menu";
            mvwprintw(window, 6, (manager::kMenuSize.colonna - strlen(start)) / 2, start);
            char quit[] = "Premere <Q> per abbandonare";
            mvwprintw(window, 8, (manager::kMenuSize.colonna - strlen(quit)) / 2, quit);
        }
        ResizableView::render(false);
    }

    void EndView::handleScreenToSmall(manager::ViewManager *manager) {
        ScreenTooSmallView *toSmall = new ScreenTooSmallView(manager::kMenuSize);
        manager->pushView(toSmall);
    }

    const char *EndView::getName() {
        return name_;
    }

};  // namespace views