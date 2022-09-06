#pragma once

#include <ncurses.h>

#include "gamestruct/position.hpp"
#include "gamestruct/state-watcher.tpp"

/**
 * @brief è una classe che astratta per mostrare gli oggetti di
 * singolo carattere su schermo
 */
class Displayable {
  protected:
    /**
     * oggetto che contiene le ultime due posizioni dell'oggetto
     * e controlla quando cambia la posizione
     */
    StateWatcher<Position> *position_;

    StateWatcher<char> *displayChar_;

  public:
    Displayable();

    Displayable(Position current, char displayChar);

    virtual ~Displayable();

    /**
     * @brief Se la posizione o il carattere sono stati aggiornati
     * mette al posto dell'ultima posizione dell'oggetto un carattere vuoto
     */
    void clearLast(WINDOW *win);

    /**
     * @brief printa un carattere vuoto nella propria posizione
     */
    void clear(WINDOW *win);

    /**
     * @brief questa funzione si occupa di renderizzare su schermo l'oggetto.
     * Sono applicati alcuni check per rendere più efficiente il render
     */
    virtual void render(WINDOW *win, bool forced = false);

    Position getLastPosition();

    Position getPosition();

    char getDisplayChar();

    void setDisplayChar(char displayChar);

    void setPosition(Position newPosition);
};
