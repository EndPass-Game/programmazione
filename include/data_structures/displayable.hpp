#pragma once

#include <ncurses.h>

#include "position.hpp"

// ISSUE: muovere questo in una directory per classi astratte?

// Displayable: è una classe che astratta per mostrare gli oggetti
// sullo schermo
class Displayable {
  protected:  
    // Ultima posizione dell'oggetto rispetto alla finestra
    Position last_; 

    // Posizione corrente dell'oggetto rispetto alla finestra
    Position current_;

    // la char che viene printata a video
    char displayChar_;

  public:

    Displayable(Position current, char displayChar);

    // Modifica la posizione e se non è uguale a quella corrente
    void movePosition(Position newPosition);

    // Se la posizione è stata aggiornata mette al posto del carattere un carattere vuoto
    void clearLast(WINDOW* win);

    // Se la posizione è stata modificata riprinta il carattere nella posizione corrente
    void render(WINDOW* win);
};