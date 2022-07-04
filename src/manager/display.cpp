/*
Descrizione:
Questa classe si occupa di mostrare sullo schermo

Funzioni:
1. Errori
*/
#include "manager/display.hpp"

#include "manager/view-manager.hpp"
#include "views/view.hpp"
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
        updateScreenSize();
        bool changed=screenSize.isChanged();
        bool tmpChangedView;
        do{
            viewManager->last()->handleScreenBeforeRender(screenSize,viewManager,changed);
            tmpChangedView=viewManager->isChangedView();
            changed|=tmpChangedView;
        }while(tmpChangedView and !viewManager->empty());

        return changed;
    }

    void Display::gameLoop()
    {
        while (!viewManager->empty())
        {
            bool hasUpdated=checkUpdateView();
            if(!viewManager->empty()){
                viewManager->last()->render(hasUpdated);
                std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
            }
        }
    }

} // namespace manager