#include "manager/display.hpp"

#include "manager/view-manager.hpp"
#include "views/view.hpp"

namespace manager {
    Display::Display(ViewManager *viewManager)
        : viewManager(viewManager),
          screenSize(getScreenSize()),
          logger_("display") {
    }

    Size Display::getScreenSize() {
        return Size{LINES, COLS};
    }

    void Display::updateScreenSize() {
        screenSize.setCurrent(getScreenSize());
    }

    bool Display::checkUpdateView() {
        updateScreenSize();
        bool changed = screenSize.isChanged();
        if (changed) {
            logger_.info("Screen size changed %d %d", screenSize.getCurrent().riga, screenSize.getCurrent().colonna);
        }
        bool tmpChangedView;
        do {
            viewManager->top()->handleScreenBeforeRender(screenSize, viewManager, changed);
            tmpChangedView = viewManager->isChangedView();
            changed |= tmpChangedView;
            if (tmpChangedView and !viewManager->empty()) {
                logger_.info("Changed view %s", (const char *) viewManager->top()->getName());
            }
        } while (tmpChangedView and !viewManager->empty());
        return changed;
    }

    void Display::gameLoop() {
        while (!viewManager->empty()) {
            bool hasUpdated = checkUpdateView();
            if (!viewManager->empty()) {
                viewManager->top()->render(hasUpdated);
                std::this_thread::sleep_for(std::chrono::milliseconds(kSleepTime));
            }
        }
    }

}  // namespace manager