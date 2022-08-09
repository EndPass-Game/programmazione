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
    // construttore che inizializza l'oggetto changable e display char
    DisplayableString(Position current, char* displayChar);
    // elimina i pointer
    ~DisplayableString();

    Position getPosition();

    char* getDisplayString();
    void setDisplayString(char* displayChar);
    
    void setPosition(Position newPosition);

    // Se la posizione è stata aggiornata mette al posto del carattere un carattere vuoto
    void clearLast(WINDOW* win);
    void clearCurrent(WINDOW* win);

    // Se la posizione è stata modificata riprinta il carattere nella posizione corrente
    void render(WINDOW* win,bool forced=false);

};