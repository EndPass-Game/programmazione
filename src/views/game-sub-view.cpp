#include "views/game-sub-view.hpp"

namespace views
{
    GameSubView::GameSubView(WINDOW *win) : SubView(win, {0, 0}, manager::kGameAreaSize)
    {
        levelManager_=new manager::Level(manager::kGameAreaSize);
    }
    void GameSubView::handleInput(char input)
    {
        switch (input)
        {
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
    void GameSubView::render(bool force)
    {
        levelManager_->getPlayer()->move(levelManager_);
        levelManager_->render(subWin_, force);
        SubView::render(force);
    }

}; // namespace views