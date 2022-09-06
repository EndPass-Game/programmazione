# Progetto di programmazione

Giovanni Spadaccini
Simone Ruggiero
Xuanqiang Huang

Nome progetto: **Endpass**

## Compilazione ed esecuzione
È presente un makefile per aiutare nei processi di compilazione ed esecuzione del gioco.

1. Avere installato la libreria di **ncurses** per la parte grafica
2. Eseguire `make main` per creare l'eseguibile. Sarà presente nella directory `build/`
3. `make run` per eseguire il file, oppure eseguirlo con `./build/main`.


## Legenda dei caratteri del gioco
- P: il personaggio del gioco
- S: un nemico shooter
- K: un nemico kamikaze
- A: un artefatto
- C: un potere
- X: una porta chiusa
- O: una porta aperta per cambiare livello
- Muri so no rappresentati dai seguenti caratteri "-|+"

## Gameplay
Endpass, il nostro progetto, è un gioco dungeon-like senza fine a punti.
Il giocatore è un carattere che si può muovere nei livelli, interagire con oggetti, come artefatti e potere e combattere contro i nemici.

Il giocatore potrà accedere man mano a nuovi livelli, che offriranno nuovi oggetti da raccogliere o nemici da uccidere.

Il livello sarà considerato finito nel momento in cui tutti gli artefatti saranno stati raccolti e tutti i nemici presenti nel livello saranno stati sconfitti.
Quando un livello sarà finito, si apriranno automaticamente tutte le porte del livello, permettendo accesso ai livelli successivi.


### Nemici
I nemici sono di due tipi: Kamikaze o shooter.

**Kamikaze**
Sono delle entità che si suicidano causando danno a contatto del player

**Shooter**
Sono delle entità che sparano a vista al player nel caso abbiano la linea di tiro libera.

## Assets
In questa directory sono presenti i file da cui vengono generate tutte le mappe del gioco, è quindi fondamentale tenere questa directory nel modo in cui è provvisto per evitare errori di runtime durante l'avvio del gioco.

Per questo motivo **non è possibile eseguire il main direttamente dalla directory di build**.

## Note
Il progetto è stato sviluppato e testato su sistema operativo linux, non è quindi garantito il corretto funzionamento su altri sistemi operativi
