#pragma once

#include "level.hpp"
#include "size.hpp"
#include "menu_state.hpp"
#include "resizableWindow.hpp"

namespace manager{
    class Menu: graphics::ResizableWindow{
    public:
        Menu();
        Level *runMenu();

    private:
        void calcSize();
        void handleScreenSizeChange();
        void recenterWindows();
        void createWindows();
        void deleteWindows();
        enums::MenuState menuState_;
        const Size kAsciiArtSize{4, 40};
        Size windowsSize_;
        WINDOW *asciiArtWin_;
        const int padding = 1;
        const char *kAsciiArt[4] = {
            "   ___  _  __ __   ___   _    ___   ___",
            "  / _/ / |/ //  \\ / o |.' \\ ,' _/ ,' _/",
            " / _/ / || // o |/ _,'/ o /_\\ `. _\\ `.",
            "/___//_/|_//__,'/_/  /_n_//___,'/___,' "};
    };
};