#include "views/resizableView.hpp"

namespace views{
    ResizableView::ResizableView(Position pos,Size s):View(pos,s){
    }

    Position ResizableView::recenterWindow(Size screen){
        int  newRiga=(screen.riga-winSize.riga)/2;
        int  newColonna=(screen.colonna-winSize.colonna)/2;
        mvwin(window,newRiga,newColonna);
    }


    void ResizableView::handleScreenBeforeRender(Changeable<Size> &screen,manager::ViewManager *view){
        
        if(screen.isChanged() and screen.getCurrent()<winSize){
            handleScreenToSmall(); 
        }else if(screen.isChanged()){
            recenterWindow(screen.getCurrent());
        }
    }

}; // namespace views


