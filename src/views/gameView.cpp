#include "views/gameView.hpp"

namespace views
{

    GameView::GameView(Position pos) : ResizableView(pos, manager::kGameWindowsSize) {}

    void GameView::handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view)
    {
        ResizableView::handleScreenBeforeRender(screen, view);
        if (quit)
        {
            view->popView();
        }
    }

    void GameView::handleInput(char input)
    {
        if (input == 'q')
        {
            quit = true;
        }
    }

    void GameView::render(bool force)
    {

        mvwprintw(window, 0, 0, "#");
        for (int i = 0; i < manager::kGameWindowsSize.riga; i++)
        {
            mvwprintw(window, i, 0, "#");
            mvwprintw(window, i, manager::kGameWindowsSize.colonna - 1, "#");
        }
        for (int i = 0; i < manager::kGameWindowsSize.colonna; i++)
        {
            mvwprintw(window, 0, i, "#");
            mvwprintw(window, manager::kGameWindowsSize.riga - 1, i, "#");
        }

        ResizableView::render(force);
    }

}; // namespace views