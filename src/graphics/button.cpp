#include "button.hpp"

namespace graphics{

    Button::Button(Size size, Position pos, char *title) : Window(size, pos), title(title)
    {
        hover = new Changeable<bool>(false);
    }

    void Button::render(bool force){
        if(hover->isChanged() or hover->isFirstValue() or force){
            box(getWindow(),0,0);
            int row=Window::getSize().x/2+ ((Window::getSize().x%2==0)?0:1);
            int col=0;//TODO:cal with the strlen(title);
            mvwprintw(getWindow(),row,col, (hover->getCurrent())?" ":"-");
            mvwprintw(getWindow(),row,col+1, title);
        }
    }

    void Button::setHover(bool isHover) { return hover->setCurrent(isHover); }
    bool Button::isHover() { return hover->getCurrent(); }

    Button::~Button()
    {
        delete hover;
    }

};