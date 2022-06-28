#include "level/collider.hpp"

#include "datastruct/vector.hpp"
#include "level/enums/state.hpp"
#include "level/wall.hpp"
#include "gamestruct/position.hpp"
#include "gamestruct/size.hpp"
namespace level {
    Collider::Collider() {
        state_ = datastruct::Vector<datastruct::Vector<enums::State>>(0);
        size_ = {0, 0};
    }
    Collider::Collider(Size size) {
        size_ = size; 
        state_.resize(size.riga);
        for (int i = 0; i < size.riga; i++) {
            state_[i].assign(size.colonna, enums::State::EMPTY);
        }
    }
    Collider::~Collider() = default; 

    enums::State Collider::getState(Position pos) const {
        return state_[pos.riga][pos.colonna];
    }

    bool Collider::hasCollided(Position pos) const {
        if (state_[pos.riga][pos.colonna] != enums::State::EMPTY) {
            return true;
        } else {
            return false; 
        }
    }

    void Collider::setState(Position pos, enums::State state) {
        state_[pos.riga][pos.colonna] = state;
    }

    void Collider::moveState(Position oldpos, Position newpos) {
        state_[newpos.riga][newpos.colonna] = state_[oldpos.riga][oldpos.colonna];
        state_[oldpos.riga][oldpos.colonna] = enums::State::EMPTY;
    }
}