#include "views/game-view.hpp"
#include "manager/level.hpp"


// TODO(gio): fixa gli include di questo file, segui la filosofia: "includi quello che usi"
// https://google.github.io/styleguide/cppguide.html#Include_What_You_Use

namespace views
{

    GameView::GameView(Position pos): 
      ResizableView(pos, manager::kGameWindowsSize) {
        levelManager_ = new manager::Level();
        gameSubView_ = new GameSubView(window,levelManager_);
        itemSubView_  =  new ItemSubView(window,levelManager_);
    }

    GameView::~GameView() {
        delete levelManager_;
        delete gameSubView_;
        delete itemSubView_;
    }

    bool GameView::handleScreenBeforeRender(StateWatcher<Size> &screen, 
      manager::ViewManager *view, bool changedView) {
        if(ResizableView::handleScreenBeforeRender(screen, view,changedView))
            return true;

        if (quit) {
            view->popView();
        } else if (pause) {
            PauseView* pauseView = new PauseView({0,0});
            view->pushView(pauseView);
            pause=false;
        }
        return false;
    }

    void GameView::handleInput(char input) {
        switch(input){
            case 'q':
                quit=true;
                break;
            case 'p':
                pause=true;
                break;
            default:
                gameSubView_->handleInput(input);
                break;
        }
    }

    void GameView::render(bool force) {
        // TODO(ang): function that has to handle all the creature moves
        itemSubView_->render(force);
        gameSubView_->render(force);
        ResizableView::render(force);
    }

    void GameView::handleScreenToSmall(manager::ViewManager* manager) {
        PauseView* pauseView = new PauseView({0,0});
        manager->pushView(pauseView);
        ScreenTooSmallView* toSmall = new ScreenTooSmallView(manager::kGameWindowsSize);
        manager->pushView(toSmall);

    }

}; // namespace views