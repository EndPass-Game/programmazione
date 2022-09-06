#pragma once
#include <ncurses.h>  // WINDOW

#include "manager/level.hpp"
#include "views/sub-view.hpp"

namespace views {
    /**
     * @brief classe che mostra alcune informazioni sul gioco
     * durante il gioco:
     * es:
     * vita del giocatore
     * numero di power del giocatore
     * punteggio del giocatore
     */
    class ItemSubView : SubView {
      private:
        manager::Level *levelManager_;

      public:
        ItemSubView(WINDOW *win, manager::Level *levelManager);

        void render(bool force);
    };
};  // namespace views