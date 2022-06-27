/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori
*/
#pragma once

#include <ncurses.h>

#include "manager/viewManager.hpp"

namespace manager
{

  // Decide ogni quanti millisecondi avviene un update a schermo
  const int kSleepTime = 50;

  class Display
  {
  private:
    ViewManager *viewManager;

  public:
    Display(ViewManager *viewManager);
    void gameLoop();
  };
}