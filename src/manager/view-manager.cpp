#include "manager/view-manager.hpp"

#include "datastruct/stack.tpp"
#include "views/view.hpp"

// TODO(gio): fixa gli include di questo file, segui la filosofia: "includi quello che usi"
// https://google.github.io/styleguide/cppguide.html#Include_What_You_Use

namespace manager {

    ViewManager::ViewManager()
        : stackView() {}

    void ViewManager::pushView(views::View *newView) {
        stackView.push(newView);
        changedView = true;
    }
    void ViewManager::popView() {
        views::View *v = stackView.pop();
        delete v;
        changedView = true;
    }
    views::View *ViewManager::last() {
        return stackView.last();
    }

    void ViewManager::clear() {
        while (!empty()) {
            popView();
        }
    }

    bool ViewManager::isChangedView() {
        if (changedView) {
            changedView = false;
            return true;
        }
        return false;
    }

    bool ViewManager::empty() {
        return stackView.isEmpty() != 0;
    }

};  // namespace manager