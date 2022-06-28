#include "manager/viewManager.hpp"

namespace manager
{

    ViewManager::ViewManager():stackView(){
    }
    void ViewManager::pushView(views::View *newView)
    {
        stackView.push(newView);
        changedView=true;
    }
    void ViewManager::popView()
    {
        stackView.pop();
        changedView=true;
    }
    views::View *ViewManager::last()
    {
        return stackView.last();
    }

    bool ViewManager::isChangedView(){
        if(changedView){
            changedView=false; 
            return true;
        }
        return false;
    }

    bool ViewManager::empty()
    {
        return stackView.isEmpty() == 0;
    }

};
