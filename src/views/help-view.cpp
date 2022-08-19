
#include "views/help-view.hpp"

namespace views {

    HelpView::HelpView(Position pos)
        : ResizableView(pos, manager::kGameWindowsSize), name_("Keys View") {}

    bool HelpView::handleScreenBeforeRender(StateWatcher<Size> &screen, manager::ViewManager *view, bool changedView) {
        if (ResizableView::handleScreenBeforeRender(screen, view, changedView))
            return true;
        if (quit) {
            view->clear();
        } else if (returnToGame) {
            view->popView();
        }
        return false;
    }

    void HelpView::handleInput(char input) {
        switch (input) {
            case ' ':
                returnToGame = true;
                break;
            case 'q':
                quit = true;
                break;
        }
    }

    void HelpView::render(bool force) {
        if (force) {
            struct KeyDescription {
                char key;
                char const *message;
            };
            const int numberKey = 8;
            KeyDescription keyDesc[numberKey] = {
                {'a', "muovi a destra"},
                {'s', "muovi in basso"},
                {'w', "muovi in alto"},
                {'d', "muovi a destra"},
                {'j', "spara"},
                {'p', "mette in pausa"},
                {'q', "termina il gioco"},
                {'h', "apre la schermata con i comandi"}};

            for (int currentKey = 0; currentKey < numberKey; currentKey++) {
                char key = keyDesc[currentKey].key;
                char const *message = keyDesc[currentKey].message;
                mvwprintw(window, currentKey * 2, (manager::kGameWindowsSize.colonna - (strlen(message) + 5)) / 2, "'%c': %s", key, message);
            }

            char riprendere[] = "Premere la barra spaziatrice per riprendere.";
            mvwprintw(window, (manager::kGameWindowsSize.riga) - 3, (manager::kGameWindowsSize.colonna - strlen(riprendere)) / 2, riprendere);
            char uscire[] = "Q per uscire";
            mvwprintw(window, (manager::kGameWindowsSize.riga) - 1, (manager::kGameWindowsSize.colonna - strlen(uscire)) / 2, uscire);
        }
        ResizableView::render(force);
    }

    void HelpView::handleScreenToSmall(manager::ViewManager *manager) {
        ScreenTooSmallView *screenToSmall = new ScreenTooSmallView(manager::kGameWindowsSize);
        manager->pushView(screenToSmall);
    }

    const char *HelpView::getName() {
        return name_;
    }

};  // namespace views