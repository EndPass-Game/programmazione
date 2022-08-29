#pragma once

#include "views/game-view.hpp"
#include "views/resizable-view.hpp"
#include "manager/manager-settings.hpp"

namespace views {
    class EndView : public ResizableView {
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

        // fa il override di questa funzione da view
        bool handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView);

        // fa il override di questa funzione da view
        void handleInput(char input);

        // fa il override di questa funzione da view
        void render(bool force);

        void handleScreenToSmall(manager::ViewManager *manager);

        const char *getName();
    };
};  // namespace views