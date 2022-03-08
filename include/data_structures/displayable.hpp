#pragma once

#include <ncurses.h>

#include "position.hpp"
#include "changeable.hpp"

//TODO:bisogna poter includere questo file


// ISSUE: muovere questo in una directory per classi astratte?

// Displayable: è una classe che astratta per mostrare gli oggetti
// sullo schermo
class Displayable {
  protected:  
    //oggetto che contiene le ultime due posizioni dell'oggetto
    //e controlla quando cambia la posizione
    Changeable<Position> *position;

    // la char che viene printata a video
    char displayChar_;

  public:

    //construttore che inizializza l'oggetto changable e display char
    Displayable(Position current, char displayChar);
    //elimina i pointer
    ~Displayable();

    //
    Position getPosition();

    // Modifica la posizione e se non è uguale a quella corrente
    void movePosition(Position newPosition);

    // Se la posizione è stata aggiornata mette al posto del carattere un carattere vuoto
    void clearLast(WINDOW* win);

    // Se la posizione è stata modificata riprinta il carattere nella posizione corrente
    void render(WINDOW* win,bool forced=false);

};