/*
Dati:
1. vite 
2. posizione 
3. danno

Funzioni
1. display
2. muovi
4. attacco
5. Interagisci (collectibles porte)
6. Mostra / non-mostrare Barra vita (?)

Altro
1. Inventario ( Classe apparte? )
*/
#include "Player.hpp"

Player::Player():Display(Position{1,1},'P'),direction(NONE){}

void Player::move(LevelManager* level){
    int new_x=current.x,new_y=current.y;
    switch(this->direction){
        case Direction::UP:
            new_x-=1;
            break;
        case Direction::RIGHT:
            new_y+=1;
            break;
        case Direction::LEFT:
            new_y-=1;
            break;
        case Direction::DOWN:
            new_x+=1;
            break;
        case Direction::NONE:
        //TODO:questa non piacerà al prof
            return;
            break;
    }
    if(canMove(new_x,new_y,level)){
        movePosition({new_x,new_y});
    }
    this->direction=Direction::NONE;
}

bool Player::canMove(int x,int y,LevelManager* level){
    return (x>0 and y>0) and
        (x<level->WINDOWS_SIZE_X-1 and y<level->WINDOWS_SIZE_Y-1);
}

