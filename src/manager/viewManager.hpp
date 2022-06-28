#pragma once

#include "datastruct/stack.hpp"


namespace manager{
    class ViewManager;
};

#include "views/view.hpp"

namespace manager{

    // la size della finersta
    const Size kGameWindowsSize  = {18,60};

    // Decide ogni quanti millisecondi avviene un update a schermo
    const int kSleepTime = 50;

    // Descrive ogni quanti frame si può muovere un nemico
    const int kObjectTimer = 10;

    class ViewManager
    {
    private:

        datastruct::Stack<views::View*> stackView;
        bool changedView=false;

    public:
        ViewManager();

        void pushView(views::View *v);

        void popView();

        bool empty();

        bool isChangedView();


        views::View* last();
    };

};