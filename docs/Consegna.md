# Progetto di Programmazione 2021/2022

### Membri del Gruppo

Xuanqiang Huang : 0001030271  
Giovanni Spadaccini : 0001021270  
Simone Ruggiero : 0001021768  


## Divisione dei compiti

### Huang

1. Gestione e caricamento di tutti i livelli
2. Gestione del cambio di livello e l'esplorazione graduale dei livelli.
3. Ideazione ed implementazione dell'intera logica per i muri, porte mostrate nel livello.

### Spadaccini

1. Studio di ncurses per creare delle astrazioni, per facilitare l'utilizzo della libreria
2. Creazione del sistema a stack per le View, creazione e rendering di tutte le schermate nel gioco
3. Creazione di `log-queue` e altre stutture per gestire gli oggetti nell'interfaccia
   

### Ruggiero

1. Creazione e gestione di tutte le entità (nemici e player)
2. Ideazione ed implementazione della logica per gli artefatti
3. Creazione della logica per i poteri

## Metodi di lavoro

Ognuno ha lavorato a stretto contatto con gli altri per quanto riguarda le classi che mettono assieme campi di competenza diversi come per esempio il `level::Level` che collegava la gestione del livello a tutti i nemici, giocatore, artefatti e poteri, o come il `Displayable`, la classe astratta da cui dipendono molti oggetti del gioco per essere mostrati su schermo.


Per il resto del progetto ognuno ha lavorato principalmente in modo asincrono, utilizzando il sistema di Pull Request offerto da Github: data una nuova feature, l’autore creava una Pull Request che veniva letta e criticata opportunamente dal resto del gruppo

### Files di gruppo

Esistono alcuni files e directory in particolare che sono stati frutto di cooperazione da parte di tutto il gruppo:

- `loader/objects/` in cui vengono caricati tutti gli oggetti da file di configurazione di livello.

- `level::Level` e `manager::Level` che sono i gestori dei livelli, il primo gestisce il singolo livello, e il secondo gestisce l'insieme di tutti i livelli della partita.

- `gamestructs/` che introducevano alcune strutture utili per tutti.

- `enums/` in cui sono raccolti alcuni enums utili per tutti.

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

## Huang

<!--

Eccetto per i file elencati in [Files di gruppo](#files-di-gruppo), il lavoro svolto in autonomia è racchiuso nelle directory

- `loaders`
  
- `level`

-->

### Loaders

I loaders si interessano del caricamento dei file di descrizione per i singoli livelli e dalla loro traduzione in oggetti del gioco.
Sono presenti 4 classi principali:

1. `loader-handler` è la classe che gestisce il caricamento del singolo livello
   
2. `directory-loader` è la classe che trova i file di descrizione delle mappe nella directory assets
   
3. `level-provider` è un singoletto il cui scopo è creare il livello (`level::Level`) a seconda della richiesta
   
4. `load-object` è una classe astratta che implementa tutte le funzioni utili alla creazione e del caricamento dei singoli oggetti che costituiscono un livello; le implementazioni di questa classe per i vari oggetti sono sotto `loader/objects/`


### Level

In questa directory sono presenti classi utili a rappresentare i muri e le porte (oltre al `level::Level` che le gestisce).


**Descrizione delle classi astratte**

- `Collidable` descrive ogni oggetto che può essere gestito come elemento di collisione in `level::Level`, tra cui tutte le tre classi concrete in questa directory e tutte le classi concrete in `entities`
  
- `Openable` descrive in modo astratto un oggetto che si può aprire e chiudere. In questa directory è implementato da entrambe le classi porte
  
- `Segment` descrive un oggetto segmento generico parallelo agli assi, per questo motivo lo si è codificato tramite una posizione iniziale una direzione e una lunghezza, invece che con posizione iniziale e finale.
  
- `displayable-segment` eredita da segment, e descrive un segmento che si può mostrare a schermo.

**Descrizione delle classi concrete**

- `door-segment` rappresenta una porta che conduce ad un altro livello collegato tramite un indice in `manager::Level`.
  
- `local-door` rappresenta una porta all'interno di una stanza del singolo livello. È collegato tramite al suo ID interno a un `collectables::Power`, che la sblocca.
  
- `wall-segment` rappresenta un segmento di muro che né `Player` né  nemici possono attraversare

## Spadaccini

### View

Nella directory view sono presenti tutte le schermate mostrate nel gioco. La classe astratta `view::View` descrive le funzioni principali che tutte le singole view possiedono devono implementare.  I principali metodi di `view::View` sono:

- `View::render`: prende in input un booleano che decide se la renderizzazione dello scermo può essere fatta in maniera lazy (cioè scrivere solo le differenze rispetto alla vecchia schermata)
  
- `View::handleInput`: Gestisce gli input provvisti a ogni frame dal `manager::Input`
  
- `View::handleScreenBeforeRender`: viene eseguita prima del render e serve sia per cambiare finestra; inoltre gli vengono passate le informazioni sulla dimensione della finestra così può essere gestita il resize
  
- `View::getName`: funzione utilizzata ai fini di debug

### View Manager
Gestisce la view mostrata a schermo tenendo uno stack contenente le view, l'ultima inserita è quella che viene eseguita in un determinato momento. Tenendo lo stack si può facilmente passare da una view all'altra senza perdere lo stato della view che viene salvato nello stack.
Quando il View manager non ha view il programma termina.


### Gestione dell'input e output
Per la gestione dell'input e dell'output abbiamo deciso dopo varie prove di utilizzare due thread, uno dedicato alla lettura da input e l'altro dedicato a la renderizzazione dei contenuti e al output di essi.  
Il vantaggio principale è l'assenza di checks per eliminare input troppo veloci e non perdere input se fossero passati durante la fase di output/calcolo.

- `manager::Display` : tiene aggiornata la posizione della finestra e la passa a `View::handleScreenBeforeRender`. Inoltre in caso di cambiamenti come il cambiamento delle dimensioni della finestra o il cambiamento della view, chiama `View::render` con il force a true. 

- `manager::Input` : legge l'input dall'utente e lo passa chiamando `View::handleInput` alla view corrente.

## Ruggiero

La mia parte è stata caratterizzata principalmente dallo sviluppo delle meccaniche di gameplay del gioco, quindi dalla creazione e dalla gestione delle varie entità (nemici e il player), degli oggetti presenti nei livelli e del loro funzionamento.

### Entity

La classe astratta su cui si basano tutte le entità è la classe `Entity`, nella quale sono presenti i metodi virtuali, utili a gestire le collisioni,e l'attacco.
Implementandola permette ad ogni entità di gestirle in maniera differente questi aspetti oltre a gestire il compito di renderizzare tutte le entità che fanno parte del gioco.
Le principali classi che la implementano sono `Player` e `Enemy`.

### Player

Questa classe contiene tutti i membri e i metodi che perettono al giocatore di muoversi, attaccare e interagire con la mappa
Le funzioni virtuali per gestire collisioni ereditate dalla classe `Entity` sono overridate e modificate in base all'utilizzo. 

### Enemy

Questa classe definisce tutti i membri e tutti i metodi comuni a tutte le tipologie di nemici. Possiede delle funzioni virtuali come `wander` che sono implementate in modo differente a seconda della tipologia di nemico.

### Shooter

Classe che rappresenta un nemico capace di sparare proiettili nel momento in cui il giocatore entra nella sua linea di tiro. Questa entità si muoverà cercando di tenersi a distanza dal giocatore e cercando di allinearsi con lui in modo da averlo a portata di tiro.

### Kamikaze

Questa classe rappresenta un nemico che insegue il giocatore e esplode causando danno al giocatore.

### Artifact

Questa classe rappresenta un collezionabile presente sulla mappa che permette di aumentare la vita massima del giocatore. Ogni artefatto sulla mappa aumenta la vita di un valore diverso, in base alla difficoltà del livello.

### Power

Classe che rappresenta un collezionabile presente sulla mappa, che restituisce vita al giocatore e apre una porta a lui collegata che permette l'accesso ad un artefatto altrimenti irraggiungibile.
