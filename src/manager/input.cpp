#include "manager/input.hpp"

#include <ncurses.h>

#include "entities/player.hpp"
#include "manager/game.hpp"
#include "manager/level.hpp"

namespace manager
{
    Input::Input(ViewManager *manager) : viewManager(manager) {}

    void Input::run()
    {
        timeout(300);
        while (!viewManager->empty())
        {
            int current_input = getch();
            if (current_input != -1)
            {
                viewManager->last()->handleInput(current_input);
            }
        }
    }
} // namespace manager