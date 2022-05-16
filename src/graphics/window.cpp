#include "window.hpp"

namespace graphics
{
    Window::Window(Position position,Size size):position_(position),size_(size) {
        win_=newwin(size.x,size.y,position.x,position.y);
    }

    Window::~Window(){
        delwin(win_);
    }
    WINDOW* Window::getWindow(){return win_;}
    Size Window::getSize(){return size_;}

    void Window::moveWindow(Position pos){
        position_=pos;
        mvwin(win_,pos.x,pos.y);
    }


};