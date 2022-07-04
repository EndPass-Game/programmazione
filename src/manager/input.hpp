/*
 *  Descrizione:
 *  Questa classe gestisce tutti gli input del gioco
 *  e chiama le funzioni corrette a seconda dell'input
 *
 */
#pragma once

#include "manager/level.hpp"
#include "manager/view-manager.hpp"

namespace manager
{
  class Input
  {
  private:

    ViewManager *viewManager;

  public:

    Input(ViewManager *viewManager);
    //funzione che viene eseguita finché rimangono elementi nel viewmanager
    void run();

  };
}