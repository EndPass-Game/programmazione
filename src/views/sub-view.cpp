#include "views/sub-view.hpp"

namespace views
{

    SubView::SubView(WINDOW * win,  Position pos,Size size)
    {
        subWin_=derwin(win,size.riga,size.colonna,pos.riga,pos.colonna);
    }
    SubView::~SubView()
    {
        delwin(subWin_);
    }

    void SubView::render(bool force)
    {
        if(force){
            touchwin(subWin_);
            wclear(subWin_);
        }
        wsyncup(subWin_);
    }
}; // namespace views