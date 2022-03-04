#pragma once
#include "DisplayManager.hpp"
#include "InputManager.hpp"
#include "LevelManager.hpp"
#include <thread>
#include <ncurses.h>


// Singoletto: unica istanza di GameManager
// Che deve gestire ad alto livello anche tutte le altre istanze
// di managers, e si occupa di creare i due loop del gioco
// in due thread
class GameManager {
private:
    //È il
    LevelManager levelManager;
    DisplayManager displayManager;
    InputManager inputManager;

    //istanza del singleton
    static GameManager *instance;

    // Design-issue: Invece di chiamaretutti i file "manager"
    // TODO: Possiamo mettere tutti questo in un namespace Manage
    // in cui stanno tutti i manager
public:
    GameManager();
    //~GameManager();

    //ritorna l'istanza del singoletto
    static GameManager* GetInstance();

    //Crea i thread e gestisce i menu prima e dopo il gioco
    void run();
};

