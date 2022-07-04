#pragma once

#include "views/screenToSize.hpp"
#include "views/resizableView.hpp"
#include "views/pauseView.hpp"
#include "manager/viewManager.hpp"
#include "manager/level.hpp"
#include "views/gameView.hpp"
#include "views/itemSubView.hpp"
#include "views/gameSubView.hpp"

namespace views
{
    class GameView : public ResizableView
    {
    private:
        // TODO: variabili per cunicare tra i due thread in un futuro andranno wrappate in una struct o classe mutex protected
        bool quit = false;
        bool pause = false;
        GameSubView * gameSubView_;
        ItemSubView * itemSubView_;
    public:
        GameView(Position pos);
        ~GameView();
        bool handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView);

        void handleInput(char input);

        void render(bool force);

        void renderItem(bool force);
        void renderGame(bool force);

        void handleScreenToSmall(manager::ViewManager* manager);
    };
}; // namespace views