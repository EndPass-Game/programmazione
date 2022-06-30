#include "views/screenToSize.hpp"

namespace views{

    ScreenToSmallView::ScreenToSmallView(Size minScreen):minimumRequired_(minScreen),View({0,0},{0,0}){ }
    void ScreenToSmallView::handleInput(char input){
        if(input=='q'){
            quit_=true;
        }
    }
    void ScreenToSmallView::render(bool force){
        wprintw(window,"Schermo troppo piccolo");
        View::render(force);
    }

    bool ScreenToSmallView::handleScreenBeforeRender(Changeable<Size> &screen, manager::ViewManager *view,bool changedView){
        if(screen.getCurrent()<=minimumRequired_){
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

