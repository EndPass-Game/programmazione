#include "views/gameView.hpp"

namespace views
{

    GameView::GameView(Position pos) : ResizableView(pos, manager::kGameWindowsSize) { }

    bool GameView::handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView)
    {
        if(ResizableView::handleScreenBeforeRender(screen, view,changedView))
            return true;
        if (quit)
        {
            view->popView();
        }else if(pause){
            PauseView* pauseView=new PauseView({0,0});
            view->pushView(pauseView);
            pause=false;
        }
        return false;
    }

    void GameView::handleInput(char input)
    {
        switch(input){
            case 'q':
                quit=true;
                break;
            case 'p':
                pause=true;
                break;
            case 'w':
                levelManager.player->setDirection(enums::Direction::UP);
                break;
            case 'a':
                levelManager.player->setDirection(enums::Direction::LEFT);
                break;
            case 'd':
                levelManager.player->setDirection(enums::Direction::RIGHT);
                break;
            case 's':
                levelManager.player->setDirection(enums::Direction::DOWN);
                break;
        }
    }

    void GameView::render(bool force)
    {
        
        levelManager.player->move();
        levelManager.player->clearLast(window);
        levelManager.player->render(window,force);
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

    void GameView::handleScreenToSmall(manager::ViewManager* manager){
        PauseView* pauseView=new PauseView({0,0});
        manager->pushView(pauseView);
        ScreenToSmallView* toSmall=new ScreenToSmallView(manager::kGameWindowsSize);
        manager->pushView(toSmall);

    }

}; // namespace views