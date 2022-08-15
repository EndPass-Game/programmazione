#include "level/displayable-segment.hpp"

#include <ncurses.h>

#include "enums/wall-type.hpp"
#include "gamestruct/displayable.hpp"

namespace level {
    DisplayableSegment::DisplayableSegment()
        : Segment() {}

    DisplayableSegment::DisplayableSegment(const Segment &segment)
        : Segment(segment) {
        Position pos = startPosition_;
        displayables_.resize(length_);
        for (int i = 0; i < length_; i++) {
            displayables_[i] = new Displayable(pos, (char) enums::WallType::DEFAULT);
            pos += posDirection_;
        }
    }

    DisplayableSegment::DisplayableSegment(Position startPosition, enums::Direction direction, int length)
        : DisplayableSegment(Segment(startPosition, direction, length)) {}

    DisplayableSegment::~DisplayableSegment() {
        for (int i = 0; i < length_; i++) {
            delete displayables_[i];
        }
    }

    void DisplayableSegment::render(WINDOW *win, bool force) {
        for (int i = 0; i < length_; i++) {
            displayables_[i]->render(win, force);
        }
    }

    void DisplayableSegment::clear(WINDOW *win) {
        for (int i = 0; i < length_; i++) {
            displayables_[i]->clear(win);
        }
    }
};  // namespace level