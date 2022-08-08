#pragma once

#include <mutex>

#include "views/view.fwd.h" // forward declaration, circular dependency

#include "datastruct/stack.hpp"
#include "gamestruct/size.hpp"

namespace manager
{

    // la size della finersta
    const Size kGameWindowsSize = {22, 60};
    const Size kItemAreaSize = {5,17};
    const Size kLogAreaSize = {kItemAreaSize.riga,kGameWindowsSize.colonna-(kItemAreaSize.colonna+2)};
    const Size kGameAreaSize = {kGameWindowsSize.riga-kItemAreaSize.riga, kGameWindowsSize.colonna};

    // Decide ogni quanti millisecondi avviene un update a schermo
    const int kSleepTime = 50;

    // Descrive ogni quanti frame si può muovere un nemico
    const int kObjectTimer = 10;

    // tiene uno stack con le finestre attive, e l'ultima è quella che viene visualizzata
    class ViewManager
    {
    private:
        datastruct::Stack<views::View *> stackView;
        bool changedView = false;

    public:
        ViewManager();
        ~ViewManager();
        // cambia la view che viene visualizzata
        void pushView(views::View *v);
        // toglie una View e l'elimina
        void popView();
        // se è vuoto ritorna true
        bool empty();
        bool isChangedView();
        // ritorna la view che viene visualizzata
        views::View *last();
        // rimuove tutti gli elementi in pratica termina il programma
        void clear();
    };

}; // namespace manager