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
#include "manager/view-manager.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/state-watcher.hpp"
#include "gamestruct/logger.hpp"


namespace manager
{

  class Display
  {
  private:

    ViewManager *viewManager;
    StateWatcher<Size> screenSize;
    Size getScreenSize();
    Logger logger_= Logger("display");
    // chiama l'handleScrennSize nella view corrente
    bool checkUpdateView();
    void updateScreenSize();

  public:


    Display(ViewManager *viewManager);
    // funzione che viene eseguita finché non ci sono più view nello stack
    void gameLoop();
  };
}