#pragma once

#include "manager/display.hpp"
#include "manager/input.hpp"
#include "manager/level.hpp"

namespace manager
{
  class Game
  {
  private:

    ViewManager *viewManager_;
    Display *displayManager_;
    Input *inputManager_;

  public:

    Game();
    ~Game();

    // Crea i thread e gestisce i menu prima e dopo il gioco
    void run();
  };
}; // namespace manager