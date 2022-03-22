# Makefile Test
Da @flecart


## Introduzione
per la creazione dei test

```Makefile
.PHONY: tests
tests: $(filter-out %main.o, $(OBJS))
	@for file in $(shell ls $(TESTS)); 													\
	do																					\
		$(CC) $(CFLAGS) $(HEADER_FLAGS) -c $(TESTS)/$${file};							\
		$(CC) $(CFLAGS) $(HEADER_FLAGS) $^ "$${file%.cpp}.o" $(LINKER_FLAG) -o ./out; 	\
		./out;																			\
		rm $${file%.cpp}.o;																\
	done
	@rm ./out 
```

### Target e ricetta
- Si utilizza il tag PHONY perché vogliamo ribuildare i test ogni volta, anche se ci sono
- Chiamo questa reicetta test, e voglio avere tutti gli oggetti tranne quello che finisce per main.o, che si presume contenga il main (così non c'è conflitto col nome main)

## Ciclo di bash
Non ho trovato risorse migliori per ciclare nei file. Non potevo utilizzare $^ perché avrei
dovuto filtrare anche fra gli objects, ma io volevo solamente i test.
Ho trovato anche il comando ``` foreach ``` che si poteva utilizzare in modo simile:
```Makefile 
TEMPLATES_DIR = ./somedir

list: 
    $(foreach file, $(wildcard $(TEMPLATES_DIR)/*), echo $(file);)
```
Ma non avevo in questo caso abbastanza comandi per compilare, eseguire e cancellare.
Per questi motivi ho preferito utilizzare un ciclo di bash e fare tutto il necessario da lì.

## Le doppie $$
In makefile il simbolo del dollaro è riservato per le variabili del makefile, quindi per accedere a delle variabili del bash ho utilizzato la sintassi del $${nome_variabile}, in 
modo simile ho utilizzato la sintassi di bash per sostituire a un file che terminava in .cpp, 
l'estensione .o, in modo che avessi il file oggetto.

## Compilazione e rimozione
Una volta compilato e linkato tutto il necessario, il file temporaneo di output è hardcoded, ed è chiamato ```out``` che sarà subito rimosso sotto.
Lo stato finale, quindi, sarà solamente l'esecusione dei file **con estensione cpp** presenti
nella cartella tests.

# Fine