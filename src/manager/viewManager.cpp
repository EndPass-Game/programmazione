#include "manager/viewManager.hpp"

namespace manager
{

    ViewManager::ViewManager() : stackView()
    {
    }

    void ViewManager::pushView(views::View *newView)
    {
        stackView.push(newView);
        changedView = true;
    }
    void ViewManager::popView()
    {
        views::View *v = stackView.pop();
        delete v;
        changedView = true;
    }
    views::View *ViewManager::last()
    {
        return stackView.last();
    }

    void ViewManager::clear(){
        while(!empty()){
            popView();
        }
    }

    bool ViewManager::isChangedView()
    {
        if (changedView)
        {
            changedView = false;
            return true;
        }
        return false;
    }

    bool ViewManager::empty()
    {
        return stackView.isEmpty() != 0;
    }

}; // namespace manager