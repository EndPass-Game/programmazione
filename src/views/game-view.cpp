#include "views/game-view.hpp"

#include "manager/level.hpp"

// TODO(gio): fixa gli include di questo file, segui la filosofia: "includi quello che usi"
// https://google.github.io/styleguide/cppguide.html#Include_What_You_Use

namespace views {

    GameView::GameView(Position pos)
        : ResizableView(pos, manager::kGameWindowsSize), name_("GameView") {
        levelManager_ = new manager::Level();
        gameSubView_ = new GameSubView(window, levelManager_);
        itemSubView_ = new ItemSubView(window, levelManager_);
        logSubView_ = new LogSubView(window, levelManager_);
    }

    GameView::~GameView() {
        delete levelManager_;
        delete gameSubView_;
        delete itemSubView_;
        delete logSubView_;
    }

    bool GameView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
        if (ResizableView::handleScreenBeforeRender(screen, view, changedView))
            return true;

        if (quit_) {
            view->popView();
        } else if (pause_) {
            PauseView *pauseView = new PauseView();
            view->pushView(pauseView);
            pause_ = false;
        } else if (help_) {
            HelpView *helpView = new HelpView({0, 0});
            view->pushView(helpView);
            help_ = false;
        } else if (levelManager_->getPlayer()->isDead()) {
            manager::SharedInformation::getInstance().setLastPlayerScore(levelManager_->getPlayer()->getScore());
            view->popView();
            EndView *endView = new EndView();
            view->pushView(endView);
        }
        return false;
    }

    void GameView::handleInput(char input) {
        switch (input) {
            case 'q':
                quit_ = true;
                break;
            case 'p':
                pause_ = true;
                break;
            case 'h':
                help_ = true;
                break;
            default:
                gameSubView_->handleInput(input);
                break;
        }
    }

    void GameView::render(bool force) {
        logSubView_->render(force);
        itemSubView_->render(force);
        gameSubView_->render(force);
        ResizableView::render(force);
    }

    void GameView::handleScreenToSmall(manager::ViewManager *manager) {
        PauseView *pauseView = new PauseView();
        manager->pushView(pauseView);
        ScreenTooSmallView *toSmall = new ScreenTooSmallView(manager::kGameWindowsSize);
        manager->pushView(toSmall);
    }

    const char *GameView::getName() {
        return name_;
    }
};  // namespace views