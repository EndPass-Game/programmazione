#include "gamestruct/displayable-string.hpp"

DisplayableString::DisplayableString(Position current, char *str) {
    position_ = new StateWatcher<Position>(current);
    string_ = stringUtility::copyString(str);
    clearString_ = stringUtility::repeatChar(strlen(str), ' ');
}

DisplayableString::~DisplayableString() {
    delete position_;
    delete[] string_;
    delete[] clearString_;
}

Position DisplayableString::getPosition() {
    return position_->getCurrent();
}

char *DisplayableString::getDisplayString() {
    return string_;
}

void DisplayableString::setDisplayString(char *displayChar) {
    delete[] string_;
    string_ = stringUtility::copyString(displayChar);
}

void DisplayableString::setPosition(Position newPosition) {
    position_->setCurrent(newPosition);
}

void DisplayableString::clearCurrent(WINDOW *win) {
    mvwprintw(win, position_->getCurrent().riga, position_->getCurrent().colonna, "%s", clearString_);
}

void DisplayableString::clearLast(WINDOW *win) {
    if (position_->isChanged() or position_->isFirstValue()) {
        mvwprintw(win, position_->getLast().riga, position_->getLast().colonna, "%s", clearString_);
    }
}

void DisplayableString::render(WINDOW *win, bool forced) {
    if (forced) {
        Position current = position_->getCurrent();
        mvwprintw(win, current.riga, current.colonna, "%s", string_);
    }
}
