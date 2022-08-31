#pragma once

#include <mutex>

#include "datastruct/stack.tpp"
#include "gamestruct/size.hpp"
#include "manager/manager-settings.hpp"
#include "views/view.fwd.h"  // forward declaration, circular dependency

namespace manager {

    // tiene uno stack con le finestre attive, e l'ultima è quella che viene visualizzata
    class ViewManager {
      private:
        datastruct::Stack<views::View *> stackView;
        bool changedView = false;

      public:
        ViewManager();
        ~ViewManager() = default;
        // cambia la view che viene visualizzata
        void pushView(views::View *v);
        // toglie una View e l'elimina
        void popView();
        // se è vuoto ritorna true
        bool empty();
        bool isChangedView();
        // ritorna la view che viene visualizzata
        views::View *top();
        // rimuove tutti gli elementi in pratica termina il programma
        void clear();
    };

};  // namespace manager