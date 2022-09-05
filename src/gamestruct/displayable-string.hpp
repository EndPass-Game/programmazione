#pragma once

#include <ncurses.h>

#include "gamestruct/position.hpp"
#include "gamestruct/state-watcher.tpp"
#include "gamestruct/string-utility.hpp"

/**
 * @brief rappresenta una stringa che può essere printata a schermo
 * principalmente utilizzata nel log-queue.hpp
 */
class DisplayableString {
  protected:
    StateWatcher<Position> *position_;

    char *string_;
    char *clearString_;

  public:
    DisplayableString(Position current, char *displayChar);

    ~DisplayableString();

    Position getPosition();

    char *getDisplayString();

    void setDisplayString(char *displayChar);

    void setPosition(Position newPosition);

    void clearLast(WINDOW *win);

    void clearCurrent(WINDOW *win);

    void render(WINDOW *win, bool forced = false);
};