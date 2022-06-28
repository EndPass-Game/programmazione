#include "views/gameView.hpp"

namespace views
{

    GameView::GameView(Position pos) : ResizableView(pos, manager::kGameWindowsSize) {}

    void GameView::handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view)
    {
        if (quit)
        {
            view->popView();
        }
    }

    void GameView::handleInput(char input)
    {
        if (input == 'f')
        {
            mvwprintw(window, 1, 0, "#");
        }
        else if (input == 'q')
        {
            quit = true;
        }
    }

    void GameView::render(bool force)
    {

        mvwprintw(window, 0, 0, "#");
        ResizableView::render(force);
    }
};