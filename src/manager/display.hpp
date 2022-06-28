/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori
*/
#pragma once

#include <ncurses.h>
#include <chrono>
#include <thread>

#include "manager/viewManager.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/changeable.hpp"


namespace manager
{

  class Display
  {
  private:
    ViewManager *viewManager;

    Changeable<Size> screenSize;

    Size getScreenSize();

    bool checkUpdateView();

    void updateScreenSize();

  public:


    Display(ViewManager *viewManager);

    void gameLoop();
  };
}