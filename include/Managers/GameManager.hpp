#pragma once
#include "DisplayManager.hpp"
#include "InputManager.hpp"
#include "LevelManager.hpp"

class GameManager {
private:
    // Singoletto: unica istanza di GameManager
    // Che deve gestire ad alto livello anche tutte le altre istanze
    // di managers
    DisplayManager *displayManager;
    // TODO: aggiungere variabili per input e display

    // Design-issue: Invece di chiamaretutti i file "manager"
    // Possiamo mettere tutti questo in un namespace Manage
    // in cui stanno tutti i manager
public:
    static GameManager *instance;
    GameManager();
    ~GameManager();
    GameManager* GetInstance();

    // Inizializza il gameloop e inizia il gioco
    void run();
};

