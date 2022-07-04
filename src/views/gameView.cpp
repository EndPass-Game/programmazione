#include "views/gameView.hpp"
#include "manager/level.hpp"
namespace views
{

    GameView::GameView(Position pos) : 
        ResizableView(pos, manager::kGameWindowsSize) {
            levelManager_ = new manager::Level(manager::kGameWindowsSize);
    }

    GameView::~GameView() {
        delete levelManager_;
    }

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
                levelManager_->getPlayer()->setDirection(enums::Direction::UP);
                break;
            case 'a':
                levelManager_->getPlayer()->setDirection(enums::Direction::LEFT);
                break;
            case 'd':
                levelManager_->getPlayer()->setDirection(enums::Direction::RIGHT);
                break;
            case 's':
                levelManager_->getPlayer()->setDirection(enums::Direction::DOWN);
                break;
        }
    }

    void GameView::render(bool force)
    {
        // TODO(ang): function that has to handle all the creature moves
        levelManager_->getPlayer()->move(levelManager_);
        levelManager_->render(window, force);
        ResizableView::render(force);
    }

    void GameView::handleScreenToSmall(manager::ViewManager* manager) {
        PauseView* pauseView=new PauseView({0,0});
        manager->pushView(pauseView);
        ScreenToSmallView* toSmall=new ScreenToSmallView(manager::kGameWindowsSize);
        manager->pushView(toSmall);

    }

}; // namespace views