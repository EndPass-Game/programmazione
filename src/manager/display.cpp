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
    Display::Display(ViewManager *viewManager) : 
        viewManager(viewManager),
        screenSize(getScreenSize()) {
        }

    Size Display::getScreenSize(){
        return Size{LINES, COLS};
    }

    void Display::updateScreenSize(){
        screenSize.setCurrent(getScreenSize());
    }

    bool Display::checkUpdateView(){
        updateScreenSize();
        bool changed = screenSize.isChanged();
        if(changed){
            logger_.info("Screen size changed %d %d", screenSize.getCurrent().riga, screenSize.getCurrent().colonna);
        }
        bool tmpChangedView;
        do{
            viewManager->last()->handleScreenBeforeRender(screenSize, viewManager, changed);
            tmpChangedView = viewManager->isChangedView();
            changed |= tmpChangedView;
            if(tmpChangedView and !viewManager->empty()){
                logger_.info("Changed view %s",(const char*) viewManager->last()->getName());
            }
        }while(tmpChangedView and !viewManager->empty());
        return changed;
    }

    void Display::gameLoop()
    {
        while (!viewManager->empty())
        {
            bool hasUpdated = checkUpdateView();
            if(!viewManager->empty()){
                viewManager->last()->render(hasUpdated);
                std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
            }
        }
    }

} // namespace manager