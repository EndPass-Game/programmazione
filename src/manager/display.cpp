/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori
*/
#include "manager/display.hpp"

#include <chrono>
#include <thread>

namespace manager
{

    Display::Display(ViewManager *viewManager) : viewManager(viewManager) {}

    void Display::gameLoop()
    {
        while (viewManager->empty())
        {
            viewManager->last()->render();
            std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
        }
    }

} // namespace manager