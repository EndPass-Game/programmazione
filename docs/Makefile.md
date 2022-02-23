## Introduzione
In questo file di documentazione cerco di spiegare e documentare la struttura del nostro Makefile. 

Dividiamo la struttura del nostro makefile in tre sottoparti base per maggiore chiarezza, e andremo ad analizzarle uno a uno.

1. Definizione delle costanti
2. Creazione della lista dei file di compilazione
3. Compilazione dei file

### 1 Costanti
le righe da ``` 1-7 ``` definiscono delle costanti utili per gli step successivi.
Possiamo trovare CC il compilatore, CFLAGS, le flag da dare al compilatore per ogni file compilato singolarmente, la ``` -I headers``` è spiegata  [qui]((https://stackoverflow.com/questions/6141147/how-do-i-include-a-path-to-libraries-in-g)) in pratica sto mettendo quella path quando sto compilando, così va in automatico a cercare lì (non so ser serve potrebbe anche non serviere).

E sono anche definite costanti per le cartelle

### 2 Liste per la compilazione
La soluzione raccontata in questo paragrafo è proposta [qui](https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make)

Per makefile dobbiamo creare delle ricette, con certi nomi. Ovviamente diventerebbe eccessivo enumerare a mano tutti i file, quindi sono stati utilizzati metodi per velocizzare la enumerazione delle ricette. Andiamo a commentare il codice utilizzato per enumerare le cartelle volute.

```$(shell find $(SRC)/ -type f -name '*.cpp')```

Questo è un comando makefile di tipo *shell*, questo permette l'utilizzo di comandi di bash di linux. Sto utilizzando il comando ```find``` che cerca nella directory definita da una costante precedente in modo **ricorsivo** (tutte le sottocartelle sono cercate), gli sto dicendo il tipo di file che cerco ```-type f```  per dire che sto cercando un "file", e ```-name '*.cpp' ``` per dire che sto cercando *tutti* i file che terminano con .cpp.

```$(patsubst %.cpp,%.o,$(sources))```

Sto utilizzando il comando *patsubst* di makefile che mi permette di rinominare i file della lista in input. Sto rinominando tutti i file che terminano per *.cpp in *.o

Quindi alla fine mi ritrovo con una lista di nomefile.o che utilizzerò nella fase successiva di compilazione

### 3 La compilazione 
[Riguardo VPATH](https://www.cmcrossroads.com/article/basics-vpath-and-vpath#:~:text=The%20VPATH%20is%20a%20list,only%20used%20for%20source%20files). principalmente utile per gli header che non ho esplicitamente dichiarato.

Cerchiamo di capire ora la riga principale di compilazione.
Riguardo il comando ```addprefix``` guarda [qui](https://stackoverflow.com/questions/1322643/makefile-how-to-add-a-prefix-to-the-basename)

```
main: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS)  $(addprefix $(BUILD_FOLD)/, $(OBJS)) -o $(BUILD_FOLD)/$@)
 ```

Questo è un comando standard per makefile, è nella struttura:
```
target: ingredienti_per_compilare
  esegui comando
  se vuoi esegui altri comandi
```
Tradotto in linguaggio più comprensibile per umani: voglio un file main, che sarà creato dagli OBJS definiti nello step 2.
Sto cercando questi file in una cartella di build e sto mettendo l'output in una cartella build col nome main 

.

Analiziamo la riga principale per compilare ogni singolo file.
```
%.o : %.cpp
    mkdir -p $(BUILD_FOLD)/$@
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $(BUILD_FOLD)/$@
```
Io sto creando la cartella se non esiste (e sto creando anche le cartelle genitori) con mkdir
La particolarità di questa riga è che sta utilizzando matching con il simbolo %, infatti se un file termina per .o, sto prendendo il nome di questo file, richiedo come ingrediente nome del file.cpp, e inizio la compilazione coi comandi presenti sotto in modo simile al precedente.

Da notare sono i caratteri particolari $@, $<:
$@ significa il target, ovver in questo caso nomefile.o (quello che matcha con .o)
$< significa ingrediente, in questo caso nomefile.cpp
