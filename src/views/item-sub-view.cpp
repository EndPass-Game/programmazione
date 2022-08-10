
#include "views/item-sub-view.hpp"
#include "manager/view-manager.hpp"

namespace views
{
    ItemSubView::ItemSubView(WINDOW *win,manager::Level *levelManager) : SubView(win, {manager::kGameAreaSize.riga, 0}, manager::kItemAreaSize),levelManager_(levelManager) {
    }

    void ItemSubView::render(bool force)
    {
        SubView::render(force);
        Player* player=levelManager_->getPlayer();
        box(subWin_,0,0),
        mvwprintw(subWin_,1,2,"  vita: %5d",player->getLife());
        mvwprintw(subWin_,2,2,"powers: %5d",player->getPowers());
        mvwprintw(subWin_,3,2," score: %5d",player->getScore());
    }

}; // namespace views