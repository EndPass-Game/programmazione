#pragma once
#include "views/resizableView.hpp"
#include "manager/viewManager.hpp"

namespace views
{
    class GameView : public ResizableView
    {
    private:
        bool quit = false;

    public:
        GameView(Position pos);

        void handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view);

        void handleInput(char input);

        void render(bool force);
    };
};