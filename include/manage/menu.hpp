#pragma once

#include "level.hpp"
#include "size.hpp"
#include "menu_state.hpp"
#include "stackLayout.hpp"
#include "vector.hpp"

namespace manager{
    class Menu:public graphics::StackLayout{
    public:
        Level *runMenu();
        Menu();

        void handleScreenToSmall();
        void handleResizedScreen();

    private:
        Size windows[2] = {{4, 40}, {3, 10}};
        enums::MenuState menuState_;
        const int padding = 1;
        const char *kAsciiArt[4] = {
            "   ___  _  __ __   ___   _    ___   ___",
            "  / _/ / |/ //  \\ / o |.' \\ ,' _/ ,' _/",
            " / _/ / || // o |/ _,'/ o /_\\ `. _\\ `.",
            "/___//_/|_//__,'/_/  /_n_//___,'/___,' "};
    };
};