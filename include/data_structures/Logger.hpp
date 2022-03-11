#pragma once

#include <stdio.h>

//Questa classe contiene i metodi che permettono di registrare tutte le azioni avvenute nel gioco all'interno del file di log

class Logger{
    private:
        
        
    public:
        //variabile contenente il nome del logger

        static char *loggerFileName;

        static FILE *loggerFile;

        //istanza del singleton 
        static Logger *instance_;

        //Costruttore vuoto della classe
        Logger();

        //ritorna l'istanza del singoletto
        //crea il singleton o returna il singleton se già esistente
        static Logger* getInstance();

        //funzione che scrive nel file il messaggio corrispondente
        static void log(char *type, char *msg);
};