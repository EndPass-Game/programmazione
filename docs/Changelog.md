## Refactor, cosa è cambiato
In questo file descrivo i cambiamenti principali del primo refactor del nostro intero codebase
gli stessi punti saranno presenti anche nella descrizione del commit

1. Rinominazione di tutti i file cpp e hpp secondo uno stile più adatto agli standard c++ 
(si noti che tutti gli import sono file senza caratteri in maiuscolo)
2. Creazione del namespace per tutti i file manager
3. Creazione della cartella degli enumerator con relativo namespace
questa scelta è stata dovuta per esperienza passata. (senza averne mai chiesto il motivo)
nel periodo in cui ho provato a fare il gioco con l'altro programmatore nell'estate 2021
metteva in cartella e namespace apposito solo per enums
4. Creazione dei getter e dei setter necessari per le classi (utilizzo di nomi in _variabileclasse
per i variabili membro per le classi (nome che suggerisce il suo essere privato, favorisce 
encapsulazione))
5. Aggiunda di header direttamente nel file cpp per evitare l'include transitivi 
questa scelta permette di avere uno sguardo veloce sulla provenienza dei simboli
utilizzati nel singolo file di implementazione
6. Editing di stile generale 
   1. Spazio fra comparazioni e assegnamenti
   2. Spazio fra dichiarazione di funzione e parentesi di apertura
   3. Spazio fra dichiarazione commento e l'inizio del commento
7. Eliminazione di commenti a funzioni che si descrivono da soli in displayManager eg. // create window 
sopra la funzione create window, e stessa cosa sotto.
8. Riguardo alle costanti WINDOWS_SIZE: 
   1. ho spostato queste variabili come costanti globali, perché mi sembra che siano questo il loro scopo
   non centrano niente con il livello, ma sono importanti al displaymanager per renderizzare lo schermo
   2. Ho notato che queste variabili sono utilizzate dal player per sapere se uscire dallo schermo o meno
   non credo sia lo schermo a decidere se dovere uscire o meno, ma poi il sistema di collision detection per i muri a dover decidere sto fatto.
9.  Trasformato in struct classi che per quanto implementato finora non avevano senso di essere classi (definite solamente costruttore e variabili membro), questo è stato il caso di position e LevelManager (ma come mai sto manager ha solamente quei due cosi???? non dovrebbe effettivamente controllare il livello?)
oppure ci sarebbero altre interfacce che non sono state scritte? Non so , per ora metto così.