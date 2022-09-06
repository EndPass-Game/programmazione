#pragma once

#include "views/game-view.hpp"
#include "views/static-text-view.hpp"

namespace views {
    /**
     * @brief classe che mostra la view del menù di gioco principale
     */
    class MenuView : public StaticTextView {
      private:
        bool quit_ = false;
        bool start_ = false;
        const int kAsciiArtAltezza_ = 4;
        const char *kAsciiArt_[4] = {
            "   ___  _  __ __   ___   _    ___   ___",
            "  / _/ / |/ //  \\ / o |.' \\ ,' _/ ,' _/",
            " / _/ / || // o |/ _,'/ o /_\\ `. _\\ `. ",
            "/___//_/|_//__,'/_/  /_n_//___,'/___,' "};

        void printMenu_();

      public:
        MenuView();

        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView);

        void handleInput(char input) override;

        void printText() override;
    };
};  // namespace views