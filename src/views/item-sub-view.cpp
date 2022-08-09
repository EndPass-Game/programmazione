
#include "views/item-sub-view.hpp"
#include "manager/view-manager.hpp"

namespace views
{
    ItemSubView::ItemSubView(WINDOW *win,manager::Level *levelManager) : SubView(win, {manager::kGameAreaSize.riga, 0}, manager::kItemAreaSize),levelManager_(levelManager) {
    }

    void ItemSubView::render(bool force)
    {
        SubView::render(force);
        mvwprintw(subWin_,1,1,"vita: %d  ",levelManager_->getPlayer()->getLife());
    }

}; // namespace views