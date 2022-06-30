#include "views/screenToSize.hpp"

namespace views{

    ScreenToSmallView::ScreenToSmallView(Size minScreen):minimumRequired_(minScreen),View({0,0},{0,0}){ }
    void ScreenToSmallView::handleInput(char input){
        if(input=='q'){
            quit_=true;
        }
    }
    void ScreenToSmallView::render(bool force){
        mvwprintw(window,0,0,"Schermo troppo piccolo");
        View::render(force);
    }

    bool ScreenToSmallView::handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView){
        if(screen.getCurrent().colonna>=minimumRequired_.colonna and screen.getCurrent().riga>=minimumRequired_.riga){
            view->popView();
            return true;
        }
        if(quit_){
            view->clear();
            return true;
        }
        return false;
    }

}; // namespace views

