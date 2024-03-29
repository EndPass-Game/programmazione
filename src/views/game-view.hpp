#pragma once

#include "manager/level.hpp"
#include "manager/shared-information.hpp"
#include "manager/view-manager.hpp"
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
    /**
     * @brief classe principale per la gestione di tutte le view del gioco
     */
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

        bool handleScreenBeforeRender(
            StateWatcher<Size> &screen,
            manager::ViewManager *view,
            bool changedView
        ) override;

        void handleInput(char input) override;

        void render(bool force) override;

        void handleScreenToSmall(manager::ViewManager *manager) override;

        const char *getName() override;
    };
};  // namespace views