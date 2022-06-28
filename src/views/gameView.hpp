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
        // fa il override di questa funzione da view
        void handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view);
        // fa il override di questa funzione da view
        void handleInput(char input);
        // fa il override di questa funzione da view
        void render(bool force);
    };
}; // namespace views