#pragma once


#include "views/resizable-view.hpp"
#include "manager/view-manager.hpp"
#include "views/screen-too-small.hpp"
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