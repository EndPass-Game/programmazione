#include "displayable.hpp"
#include "display.hpp"
#include "game.hpp"

Displayable::Displayable(Position current, char display_char) : 
    displayChar_(display_char) {
        position_=new Changeable<Position>(current);
    }

void Displayable::setPosition(Position new_position_) {
    position_->setCurrent(new_position_);
}

void Displayable::clearLast(WINDOW *win) {
    if (position_->isChanged()) {
        mvwprintw(win, position_->getLast().x, position_->getLast().y, " ");
    }
}

Position Displayable::getPosition(){
    return position_->getCurrent();
}
void Displayable::render(WINDOW *win,bool forced) {
    if (position_->isChanged() or position_->isFirstValue() or forced) {
        mvwprintw(win, position_->getCurrent().x, position_->getCurrent().y, "%c", displayChar_);
        setPosition(position_->getCurrent());
    }
}
Displayable::~Displayable(){
    delete position_;
}

bool Displayable::collisionDetection(int x, int y){
    manager::Level *levelManager = manager::Game::GetInstance()->getLevelManager();
    Player *player = levelManager->player;
    Enemy *enemy = levelManager->enemy;
    if(enemy->position_->getCurrent().x == x && enemy->position_->getCurrent().y == y) return false;
    if(player->position_->getCurrent().x == x && player->position_->getCurrent().y == y) return false;
    return (x > 0 && y > 0) &&
        (x < manager::kGameWindowsSize.x - 1 && y < manager::kGameWindowsSize.y - 1);
}