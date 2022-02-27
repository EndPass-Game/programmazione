#pragma once
#include "DisplayManager.hpp"
#include "InputManager.hpp"
#include "LevelManager.hpp"

class GameManager {
private:
    // Singoletto: unica istanza di GameManager
    // Che deve gestire ad alto livello anche tutte le altre istanze
    // di managers

    //  aggiungere variabili per input e display
    LevelManager levelManager;
    DisplayManager displayManager;
    InputManager inputManager;

    static GameManager *instance;

    // Design-issue: Invece di chiamaretutti i file "manager"
    // TODO: Possiamo mettere tutti questo in un namespace Manage
    // in cui stanno tutti i manager
public:
    GameManager();
    //~GameManager();
    static GameManager* GetInstance();

    // Inizializza il gameloop e inizia il gioco
    void run();
};

