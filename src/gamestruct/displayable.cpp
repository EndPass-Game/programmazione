#include "gamestruct/displayable.hpp"

Displayable::Displayable() {
    position_ = new StateWatcher<Position>(Position(0, 0));
    displayChar_ = new StateWatcher<char>(' ');
}

Displayable::Displayable(Position current, char display_char) {
    position_ = new StateWatcher<Position>(current);
    displayChar_ = new StateWatcher<char>(display_char);
}

char Displayable::getDisplayChar() {
    return displayChar_->getCurrent();
}

void Displayable::setDisplayChar(char display_char) {
    displayChar_->setCurrent(display_char);
}

void Displayable::setPosition(Position new_position_) {
    position_->setCurrent(new_position_);
}

void Displayable::clearLast(WINDOW *win) {
    if (position_->isChanged() or displayChar_->isChanged()) {
        this->clear(win);
    }
}

void Displayable::clear(WINDOW *win) {
    mvwprintw(win, position_->getLast().riga, position_->getLast().colonna, " ");
}

Position Displayable::getPosition() {
    return position_->getCurrent();
}

Position Displayable::getLastPosition() {
    return position_->getLast();
}

void Displayable::render(WINDOW *win, bool forced) {
    if (position_->isChanged() or position_->isFirstValue()) {
        setPosition(position_->getCurrent());
        forced = true;
    }

    if (displayChar_->isChanged() or displayChar_->isFirstValue()) {
        setDisplayChar(displayChar_->getCurrent());
        forced = true;
    }

    if (forced) {
        mvwprintw(win, position_->getCurrent().riga, position_->getCurrent().colonna, "%c", displayChar_->getCurrent());
    }
}

Displayable::~Displayable() {
    delete position_;
    delete displayChar_;
}