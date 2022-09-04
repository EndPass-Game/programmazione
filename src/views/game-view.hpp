#pragma once

#include "manager/level.hpp"
#include "manager/view-manager.hpp"
#include "manager/shared-information.hpp"
#include "views/end-view.hpp"
#include "views/game-sub-view.hpp"
#include "views/game-view.hpp"
#include "views/help-view.hpp"
#include "views/item-sub-view.hpp"
#include "views/log-sub-view.hpp"
#include "views/pause-view.hpp"
#include "views/resizable-view.hpp"
#include "views/screen-too-small.hpp"

namespace views {
    class GameView : public ResizableView {
      private:
        // TODO: variabili per cunicare tra i due thread in un futuro andranno wrappate in una struct o classe mutex protected
        bool quit_ = false;
        bool pause_ = false;
        bool help_ = false;
        GameSubView *gameSubView_;
        ItemSubView *itemSubView_;
        LogSubView *logSubView_;
        manager::Level *levelManager_;
        const char *name_;

      public:
        GameView(Position pos);
        ~GameView();
        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView);

        void handleInput(char input);

        void render(bool force);

        void handleScreenToSmall(manager::ViewManager *manager);

        const char *getName();
    };
};  // namespace views