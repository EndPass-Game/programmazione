
#include "views/log-sub-view.hpp"

#include "manager/view-manager.hpp"

namespace views {
    LogSubView::LogSubView(WINDOW *win, manager::Level *levelManager)
        : SubView(win, {manager::kGameAreaSize.riga, manager::kItemAreaSize.colonna + 1}, manager::kLogAreaSize),
          levelManager_(levelManager) {
    }

    void LogSubView::render(bool force) {
        box(subWin_, 0, 0);
        levelManager_->getLogQueue()->render(subWin_, force);
        SubView::render(force);
    }

};  // namespace views