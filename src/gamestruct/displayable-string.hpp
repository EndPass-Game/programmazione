#pragma once

#include <ncurses.h>

#include "gamestruct/position.hpp"
#include "gamestruct/state-watcher.hpp"
#include "gamestruct/string-utility.hpp"

class DisplayableString {
  protected:  
    StateWatcher<Position> *position_;

    char* string_;
    char* clearString_;

  public:
    DisplayableString(Position current, char* displayChar);

    ~DisplayableString();

    Position getPosition();

    char* getDisplayString();

    void setDisplayString(char* displayChar);
    
    void setPosition(Position newPosition);

    void clearLast(WINDOW* win);

    void clearCurrent(WINDOW* win);

    void render(WINDOW* win,bool forced=false);

};