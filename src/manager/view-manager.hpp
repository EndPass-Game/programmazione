#pragma once

#include <mutex>

#include "datastruct/stack.tpp"
#include "gamestruct/size.hpp"
#include "manager/manager-settings.hpp"
#include "views/view.fwd.h"  // forward declaration, circular dependency

namespace manager {
    /**
     * @brief Questa classe si occupa di gestire la view mostrata a schermo
     * tiene uno stack con le finestre attive, e l'ultima è quella che viene visualizzata
     */
    class ViewManager {
      private:
        datastruct::Stack<views::View *> stackView;
        bool changedView = false;

      public:
        ViewManager();

        ~ViewManager() = default;

        /// @brief cambia la view che viene visualizzata
        void pushView(views::View *v);

        /// @brief toglie una View e l'elimina
        void popView();

        /// @brief ritorna la view che viene visualizzata
        views::View *top();

        /// @brief rimuove tutti gli elementi in pratica termina il programma
        void clear();

        bool empty();

        bool isChangedView();
    };
};  // namespace manager