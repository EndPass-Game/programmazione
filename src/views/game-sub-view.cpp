#include "views/game-sub-view.hpp"

namespace views {
    GameSubView::GameSubView(WINDOW *win, manager::Level *levelManager)
        : SubView(win, {0, 0}, manager::kGameAreaSize), levelManager_(levelManager) {
        levelManager_->getLogQueue()->addEvent("Benvenuti nel gioco, Cliccare <h> per vedere i comandi");
    }

    void GameSubView::handleInput(char input) {
        switch (input) {
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
            case 'j':
                levelManager_->getPlayer()->attack(levelManager_);
                break;
        }
    }

    void GameSubView::render(bool force) {
        SubView::render(force);
        levelManager_->render(subWin_, force);
    }
};  // namespace views
