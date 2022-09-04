#pragma once

#include "gamestruct/string-utility.hpp"
#include "manager/manager-settings.hpp"
#include "manager/shared-information.hpp"
#include "views/game-view.hpp"
#include "views/static-text-view.hpp"

namespace views {
    class EndView : public StaticTextView {
      private:
        // TODO: variabili per cunicare tra i due thread in un futuro andranno wrappate in una struct o classe mutex protected

        bool quit_ = false;
        bool start_ = false;
        const int kAsciiArtAltezza_ = 4;
        const char *kAsciiArt_[4] = {

            "   ___  _  __ __ ",
            "  / _/ / |/ //  \\",
            " / _/ / || // o |",
            "/___//_/|_//__,'/"};

        const char *name_;

        void printMenu_();

      public:
        EndView();

        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView);

        void handleInput(char input) override;

        void printText() override;
    };
};  // namespace views