#include "views/itemSubView.hpp"
#include "manager/viewManager.hpp"

namespace views
{
    ItemSubView::ItemSubView(WINDOW *win) : SubView(win, {manager::kGameAreaSize.riga, 0}, manager::kItemAreaSize) {}

    void ItemSubView::render(bool force)
    {
        mvwprintw(subWin_,1,1,"cuore");
        SubView::render(force);
    }

}; // namespace views