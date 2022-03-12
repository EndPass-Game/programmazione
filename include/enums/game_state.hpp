#pragma once

namespace enums {
    //Game state contiene tutti gli stati che il gioco può avere durante la sua esecuzione
    enum GameState {
        //Schermata d'errore se servisse in futuro un altra schermata d'errore si dovrà generalizzare questo stato
        SCREEN_TO_SMALL,
        //il Gioco non ha problemi e sta eseguendo
        RUNNING,
        //Gioco in pausa, anche dopo un errrore
        PAUSE,
        //Gioco finito
        FINISH
    };
}