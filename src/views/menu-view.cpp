#include <cstring>

#include "views/menu-view.hpp"

namespace views
{
    MenuView::MenuView():ResizableView({0,0},kMenuSize_){ }


    // fa il override di questa funzione da view
    bool MenuView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView){
        if(ResizableView::handleScreenBeforeRender(screen,view,changedView))
            return true;
        if(quit_) {
            view->clear();
        }else if(start_){
            GameView* game=new GameView({0,0});
            view->pushView(game);
            start_=false;
        }
        return false;
    }
    // fa il override di questa funzione da view
    void MenuView::handleInput(char input){
        switch (input)
        {
        case 'q':
            quit_=true;
            break;
        case '\n':
            start_=true;
            break;
        }
    }

    void MenuView::printMenu(bool force){
        for(int riga=0;riga<kAsciiArtAltezza_;riga++){
            mvwprintw(window,riga+1,(kMenuSize_.colonna-strlen(kAsciiArt_[riga]))/2,kAsciiArt_[riga]);
        }
    }

    // fa il override di questa funzione da view
    void MenuView::render(bool force){
        printMenu(force);
        char start[]="Premere <Invio> per incominciare";
        mvwprintw(window,6, (kMenuSize_.colonna -strlen(start))/2,start);
        char quit[]="Premere 'q' per abbandonare";
        mvwprintw(window, 8 ,(kMenuSize_.colonna -strlen(quit))/2,quit);
        ResizableView::render(force);
    }

    void MenuView::handleScreenToSmall(manager::ViewManager* manager){
        ScreenTooSmallView* toSmall=new ScreenTooSmallView(kMenuSize_);
        manager->pushView(toSmall);

    }
}; // namespace views