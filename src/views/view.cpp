#include "views/view.hpp"

namespace views
{
    View::View(Position pos,Size size):winSize(size),winPosition(pos){
        window=newwin(size.riga,size.colonna,pos.riga,pos.colonna);
    }

    View::~View(){
        delwin(window);
    }

    void View::render(bool force){
        if(force)
            touchwin(window);
        wrefresh(window);
    }

}; // namespace views
