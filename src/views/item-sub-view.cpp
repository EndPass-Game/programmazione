
#include "views/item-sub-view.hpp"
#include "manager/view-manager.hpp"

namespace views
{
    ItemSubView::ItemSubView(WINDOW *win,manager::Level *levelManager) : SubView(win, {manager::kGameAreaSize.riga, 0}, manager::kItemAreaSize) {
    }

    void ItemSubView::render(bool force)
    {
        mvwprintw(subWin_,1,1,"cuore");
        SubView::render(force);
    }

}; // namespace views