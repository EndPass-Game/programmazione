/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori
*/
#include "manager/display.hpp"


namespace manager
{

    Display::Display(ViewManager *viewManager) : viewManager(viewManager),screenSize(getScreenSize()) {
    }

    Size Display::getScreenSize(){
        return Size{LINES,COLS};
    }

    void Display::updateScreenSize(){
        screenSize.setCurrent(getScreenSize());
    }

    bool Display::checkUpdateView(){
        bool changed=false;
        bool tmpChangedView;
        do{
            viewManager->last()->handleScreenBeforeRender(screenSize,viewManager);
            tmpChangedView=viewManager->isChangedView();
            changed|=tmpChangedView;
        }while(tmpChangedView);

        return changed;
    }

    void Display::gameLoop()
    {
        while (viewManager->empty())
        {
            bool hasUpdated=checkUpdateView();
            viewManager->last()->render(hasUpdated);
            std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
        }
    }

} // namespace manager