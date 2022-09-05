# Progetto di Programmazione 2021/2022
### Membri del Gruppo
Xuanqiang Huang #TODO matricola
Giovanni Spadaccini #TODO matricola
Simone Ruggiero #TODO matricola


## Divisione dei compiti
A grandi linee il progetto è stato diviso in questo modo:
### Xuanqiang
1. Gestione e caricamento di tutti i livelli
2. Gestione del cambio di livello e l'esplorazione graduale dei livelli.
3. Ideazione ed implementazione dell'intera logica per i muri, porte mostrate nel livello.

### Giovanni
1. Studio di ncurses per le astrazioni grafiche
2. Creazione del sistema a stack per le View
3. Rendering di tutte le view nel gioco
   
> TODO: decidere se è meglio lista a punti oppure questo sotto discorsivo
> 
Il mio compito è stato principalmente studiare ncourses e creare un astrazione, attraverso la quale io e i miei colleghi potessimo lavorare senza bisogno di interfacciarci con ncurese.

### Simone
1. Creazione e gestione di tutte le entità
2. Ideazione ed implementazione della logica per gli artefatti
3. Creazione della logica per i poteri

## Metodi di lavoro

> In cui andiamo a descrivere in che modo abbiamo sviluppato il progetto dal punto di vista della collaborazione in gruppo
> 

Ognuno ha lavorato a stretto contatto con gli altri per quanto riguarda le classi che mettono assieme campi di competenza diversi come per esempio il `level::Level` che collegava la gestione del livello a tutti i nemici, giocatore, artefatti e poteri, o come altro livello il `Displayable` la classe astratta da cui dipendono molti oggetti del gioco per essere mostrati su schermo.

Per il resto del progetto ognuno ha lavorato principalmente in modo asincrono, utilizzando il sistema di Pull Request offerto da Github, in modo simile a quanto si contruibuisce a un progetto Open Source lì hostato: data una nuova feature, l'autore creava una Pull Request che veniva letta e criticata opportunamente dal resto del gruppo.

### Files di gruppo
Esistono alcuni file e directory in particolare che sono stati frutto di cooperazione da parte di tutto il gruppo:
- `loader/objects/` in cui vengono caricati tutti gli oggetti da file di configurazione di livello
- `level::Level` e `manager::Level` che sono i gestori dei livelli principali.
- `gamestructs/` che introducevano alcune strutture utili per tutti
- `enums/` in cui sono raccolti alcuni enums utili per tutti
- `datastruct/` in cui sono presenti alcune strutture di dati utilizzati nell'intero progetto.

## Dettagli Tecnici

### Scelte implementative ad alto livello
Il progetto è diviso in tre macroaree:
1. Gestione della logica per oggetti del singolo livello
   1. Nemici
   2. Player
   3. Artefatti
   4. Poteri
2. Gestione della logica per la stampa a schermo
   1. Views.
   2. Print del singolo carattere.
   3. Managers generali e threads per il programma.
3. Gestione del caricamento, e spostamento fra i vari livelli:
   1. loaders dai file di descrizione
   2. manager dei livelli che contiene e gestice il movimento fra i livelli
   3. i muri e le porte del singolo livello.

Il progetto è organizzato in cartelle che seguono queste macroaree. 
A seconda delle necessità, sono stati introdotti `namespaces` che seguono il nome della directory in cui sono presenti.

## Xuanqiang
Eccetto per i file elencati in [Files di gruppo](#files-di-gruppo), il mio lavoro è racchiuso nelle directory
- `loaders`
- `level`
### Loaders
I loaders si interessano del caricamento dei file di descrizione per i singoli livelli e dalla loro traduzione in oggetti del gioco.
Sono presenti 4 classi principali:
1. `loader-handler` è la classe che gestisce il caricamento del singolo livello
2. `directory-loader` è la classe incaricata di percorrere la directory per trovare i file di descrizione delle mappe
3. `level-provider` è un singoletto il cui scopo è creare i `level::Level` a seconda della richiesta
4. `load-object` è una classe astratta che implementa tutte le funzioni utili alla creazione e del caricamento dei singoli oggetti, tranne il loading stesso, che è delegato ai `loader/objects/`
### Level
In questa directory sono presenti classi utili a rappresentare i muri e le porte (oltre al `level::Level` che le gestisce).

Qui sono presenti 4 classi da cui derivano le classi concrete
- `door-segment`
- `local-door`
- `wall-segment`

**Descrizione delle classi astratte**
- `Collidable` descrive ogni oggetto che può essere gestito come elemento di collisione in `level::Level`, tra cui tutte le tre classi concrete in questa directory e tutte le classi concrete in `entities`
- `Openable` descrive in modo astratto un oggetto che si può aprire e chiudere. In questa directory è implementato da entrambe le classi porte
- `Segment` descrive un oggetto segmento generico parallelo agli assi, per questo motivo lo si è codificato tramite una posizione iniziale una direzione e una lunghezza, invece che con posizione iniziale e finale.
- `displayable-segment` eredita da segment, e descrive un segmento che si può mostrare a schermo.

**Descrizione delle classi concrete**
- `door-segment` rappresenta una porta di livello. È collegato ad un indice di un altro livello tramite `manager::Level`.
- `local-door` rappresenta una porta all'interno di una stanza del singolo livello. È collegato tramite al suo ID interno a un `collectables::Power`, che la sblocca.
- `wall-segment` rappresenta un segmento di muro che né `Player` né  nemici possono attraversare

## Gio
### View

Rappresentano una pagina che viene renderizzata a video, ha i seguenti metodi astratti:
- `View::render` :  prende in input un booleano che gli dice se deve riscrivere tutto sullo schermo o può farlo in maniera lazy
- `View::handleInput` : prende in input una char ed è la funzione che viene eseguita ogni volta che viene preso un input
- `View::handleScreenBeforeRender` : viene eseguita prima del render e serve sia per cambiare finestra, inoltre gli vengono passate le informazioni sulla dimensione della finestra così può essere gestito il resize
- `View::getName` : funzione utilizzata ai fini di debug

### View Manager

Tiene uno stack contenente le view, l'ultima di essa è quella che sta eseguendo. Tenendo lo stack si può facilmente passare da una view all'altra senza perdere lo stato della view.
Quando il View manager non ha view il programma termina.


### Gestione dell'input e output

Per la gestione dell'input e dell'output abbiamo deciso dopo varie prove di utilizzare due thread, uno dedicato alla lettura da input e l'altro dedicato a la renderizzazione dei contenuti e al output di essi.  

Il vantaggio che abbiamo avuto e che non dobbiamo fare nessun check per eliminare input troppo veloci e non perdere input se fossero passati durante la fase di output/calcolo.

- `manager::Display` : tiene aggiornata la posizione della finestra e la passa a `View::handleScreenBeforeRender`. Inoltre in caso di cambiamenti come il cambiamento delle dimensioni della finestra o il cambiamento della view, chiama `View::render` con il force a true. Queste funzioni vengono eseguite sull'ultima view del ViewManger.

- `manager::Input` : legge l'input dall'utente e lo passa chiamando `View::handleInput` sull'ultima view nel ViewManager


### Displayable



## Simone
La mia parte è stata caratterizzata principalmente dallo sviluppo delle meccaniche di gameplay del gioco, quindi dalla creazione e dalla gestione delle varie entità e della loro suddivisione, degli oggetti presenti nei livelli e del loro funzionamento

### Entity
La classe su cui si basano tutte le entità è la classe `Entity` nella quale sono presenti tutti i metodi virtuali, come quelli per gestire le collisioni oppure per attaccare, utili alle classi che la erediteranno, in modo da permettere ad ogni entità di gestirle in maniera differente, inoltre gestisce il compito di renderizzare tutte le entità che fanno parte del gioco.
Questa classe viene ereditata dalle classi `Player` e `Enemy`
Il player viene gestito da tastiera tramite un apposito thread, mentre gli enemy sono gestiti tutti quanti dal computer.

### Player
Questa classe contiene tutti i membri e i metodi che perettono al giocatore di muoversi, attaccare e interagire con la mappa
Le funzioni virtuali per gestire collisioni ereditate dalla classe `Entity` sono overridate e modificate in base all'utilizzo. Molte classi sono fortemente collegate a questa come `Artifact` e `Power` visto che sono oggetti collezionabili dal player. 

### Enemy
Questa classe definisce tutti i membri e tutti i metodi comuni a tutte le tipologie di nemici. Possiede delle funzioni virtuali come `wander` e `canAttack` che sono implementate in modo differente a seconda della tipologia di nemico.

### Shooter
Classe che rappresenta un nemico capace di sparare proiettili nel momento in cui il giocatore entra nella sua linea di tiro. Questa entità si muoverà cercando di tenersi a distanza dal giocatore e cercando di allinearsi con lui in modo da averlo a portata di tiro.


### Kamikaze
Questa classe rappresenta un nemico che insegue il giocatore e si suicida al momento di incontro ravvicinato causando danno al giocatore.
## Scelte implementative

> Dove andiamo a descrivere perché abbiamo scelto di implementare cosa e perché