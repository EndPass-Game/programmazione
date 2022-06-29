#include "views/pauseView.hpp"

namespace views
{

    PauseView::PauseView(Position pos) : ResizableView(pos, manager::kGameWindowsSize) {}

    void PauseView::handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView)
    {
        ResizableView::handleScreenBeforeRender(screen, view,changedView);
        if (quit)
        {
            view->clear();
        } else if (returnToGame)
        {
            view->popView();
        }
    }

    void PauseView::handleInput(char input)
    {
        switch(input){
            case ' ':
                returnToGame=true;
                break;
            case 'q':
                quit=true;
                break;
        }
    }

    void PauseView::render(bool force)
    {
        char pausa[]="PAUSA";
        mvwprintw(window,(manager::kGameWindowsSize.riga)/2-2, (manager::kGameWindowsSize.colonna -strlen(pausa))/2,pausa);
        char riprendere[]="Premere la barra spaziatrice per riprendere.";
        mvwprintw(window,(manager::kGameWindowsSize.riga)/2, (manager::kGameWindowsSize.colonna -strlen(riprendere))/2,riprendere);
        char uscire[]="Q per uscire";
        mvwprintw(window,(manager::kGameWindowsSize.riga)/2+1, (manager::kGameWindowsSize.colonna -strlen(uscire))/2,uscire);
        box(window,0,0);
        ResizableView::render(force);
    }

}; // namespace views