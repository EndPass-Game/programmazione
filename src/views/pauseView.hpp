#pragma once


#include "views/resizableView.hpp"
#include "manager/viewManager.hpp"
#include "views/screenToSize.hpp"
#include <cstring>

namespace views
{
    class PauseView : public ResizableView
    {
    private:

        bool quit = false;
        bool returnToGame=false;

    public:
        
        PauseView(Position pos);
        // fa il override di questa funzione da view
        bool handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView);
        // fa il override di questa funzione da view
        void handleInput(char input);
        // fa il override di questa funzione da view
        void render(bool force);
        void handleScreenToSmall(manager::ViewManager* manager);
    };
}; // namespace views