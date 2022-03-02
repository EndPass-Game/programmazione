#pragma once
#include "Position.hpp"
#include <climits>
#include <ncurses.h>


//Display: è una classe che astrae 
class Display{
public:
    //Ultima posizione dell'oggetto rispetto alla finestra
    Position last;
    //Posizione corrente dell'oggetto rispetto alla finestra
    Position current;
    //la char che viene printata a video
    char display_char;
    //
    Display(Position current,char display_char);
    //Modifica la posizione e se non è uguale a quella corrente
    void movePosition(Position new_position);
    //Se la posizione è stata aggiornata mette al posto del carattere un carattere vuoto
    void clearLast(WINDOW* win);
    //Se la posizione è stata modificata riprinta il carattere nella posizione corrente
    void render(WINDOW* win);
};