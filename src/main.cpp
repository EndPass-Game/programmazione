
#include "GameManager.hpp"

int main(){
    GameManager* gameInstance=GameManager::GetInstance();
    gameInstance->run();
}

/*
 * PROVA GAME
#include <thread>
#include <chrono>

using namespace std;

struct Player{
    bool alive=true;
    int x=1;
    int y=1;
    char move;
    bool is_inside(int max_x,int max_y){
        max_x-=1; max_y-=1;
        if(x<1 || y<1)	return false;
        if(x>=max_x || y>=max_y)return false;
        return true;
    }
};

void gameInput(Player* p){
    while(p->alive){
        int input=getch();
        p->move=(char)input;
    }
}

void decript_input(Player *p){
    char char_input=p->move;
    if(char_input=='q'){
        p->alive=false;
    }else if(char_input=='a'){
        p->y--;					
    }else if(char_input=='s'){
        p->x++;					
    }else if(char_input=='d'){
        p->y++;					
    }else if(char_input=='w'){
        p->x--;					
    }
    p->move='\0';
}

void gameDisplay(Player* p){
    WINDOW *win;
    int max_x=8;
    int max_y=30;
    win = newwin(max_x, max_y, 0, 0);
    box(win, 1 , 1);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    refresh();
    while(p->alive){
        mvwprintw(win,p->x,p->y," ");
        decript_input(p);
        if(p->is_inside(max_x,max_y)){
            mvwprintw(win,p->x,p->y,"P");
        }else{
            p->alive=false;
            continue;
        }
        wrefresh(win);
        this_thread::sleep_for (std::chrono::milliseconds(300));
    }
    wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);
}

int main(){
    initscr();
    noecho();
    printw("inizio\n");
    Player* p=new Player;

    thread input(gameInput, p);
    input.detach();
    thread display(gameDisplay, p);
    display.join();


    printw("fine");
    refresh();
    getch();

    endwin();
    free(p);

}
*/
