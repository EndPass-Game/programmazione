#pragma once

#include "views/screenToSize.hpp"
#include "views/resizableView.hpp"
#include "views/pauseView.hpp"
#include "manager/viewManager.hpp"
#include "manager/level.hpp"
#include "views/gameView.hpp"

namespace views
{
    class GameView : public ResizableView
    {
    private:
        // TODO: variabili per cunicare tra i due thread in un futuro andranno wrappate in una struct o classe mutex protected
        bool quit = false;
        bool pause = false;
        manager::Level levelManager;

    public:
        
        GameView(Position pos);
        bool handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView);

        void handleInput(char input);

        void render(bool force);

        void handleScreenToSmall(manager::ViewManager* manager);
    };
}; // namespace views