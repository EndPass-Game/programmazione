# Progetto di Programmazione 2021/2022
### Membri del Gruppo
Xuanqiang Huang #TODO matricola
Giovanni Spadaccini #TODO matricola
Simone Ruggero #TODO matricola


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
1. Creazione e gestione di tutti i nemici
2. Ideazione ed implementazione della logica per gli artefatti
3. Creazione della logica per i poteri

## Metodi di lavoro

> In cui andiamo a descrivere in che modo abbiamo sviluppato il progetto dal punto di vista della collaborazione in gruppo
> 

Ognuno ha lavorato a stretto contatto con gli altri per quanto riguarda le classi che mettono assieme campi di competenza diversi come per esempio il `level::Level` che collegava la gestione del livello a tutti i nemici, giocatore, artefatti e poteri, o come altro livello il `Displayable` la classe astratta da cui dipendono molti oggetti del gioco per essere mostrati su schermo.

Per il resto del progetto ognuno ha lavorato principalmente in modo asincrono, utilizzando il sistema di Pull Request offerto da Github, in modo simile a quanto si contruibuisce a un progetto Open Source lì hostato: data una nuova feature, l'autore creava una Pull Request che veniva letta e criticata opportunamente dal resto del gruppo.



## Dettagli Tecnici

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




## Scelte implementative

> Dove andiamo a descrivere perché abbiamo scelto di implementare cosa e perché