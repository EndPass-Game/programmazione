#include "views/end-view.hpp"

#include <cstring>

namespace views {
    EndView::EndView()
        : StaticTextView({0, 0}, manager::kGameAreaSize, "EndView") {}

    bool EndView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
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
            mvwprintw(window, riga + 1, (manager::kGameAreaSize.colonna - strlen(kAsciiArt_[riga])) / 2, kAsciiArt_[riga]);
       }
    }

    void EndView::printText() {
        printMenu_();
        char scoreText[] = "Hai fatto uno score di:";
        mvwprintw(window, 8, (manager::kGameAreaSize.colonna - strlen(scoreText)) / 2, scoreText);
        char* score = stringUtility::intToString(manager::SharedInformation::getInstance().getLastPlayerScore());
        mvwprintw(window, 10, (manager::kGameAreaSize.colonna - strlen(score)) / 2, score);
        delete [] score;
        char start[] = "Premere <Space> per tornare al menu";
        mvwprintw(window, 12, (manager::kGameAreaSize.colonna - strlen(start)) / 2, start);
        char quit[] = "Premere <Q> per abbandonare";
        mvwprintw(window, 14, (manager::kGameAreaSize.colonna - strlen(quit)) / 2, quit);
    }

};  // namespace views