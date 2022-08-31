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
#### Gestione dell'input e output

Per la gestione dell'input e dell'output abbiamo deciso dopo varie prove di utilizzare due thread, uno dedicato alla lettura da input e l'altro dedicato a la renderizzazione dei contenuti e al output di essi.  

Il vantaggio che abbiamo avuto e che non dobbiamo fare nessun check per eliminare input troppo veloci e non perdere input se fossero passati durante la fase di output/calcolo.



#### View

#### Displayable



## Scelte implementative
> Dove andiamo a descrivere perché abbiamo scelto di implementare cosa e perché