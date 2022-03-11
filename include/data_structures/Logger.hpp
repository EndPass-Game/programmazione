#pragma once



//Questa classe contiene i metodi che permettono di registrare tutte le azioni avvenute nel gioco all'interno del file di log
class Logger{
    private:
        //variabile contenente il nome del logger
        char *loggerName;

        
        
    public:
        //istanza del singleton 
        static Logger *instance_;
        
        //Costruttore vuoto della classe
        Logger();

        //ritorna l'istanza del singoletto
        //crea il singleton o returna il singleton se già esistente
        static Logger* getInstance();

        //funziona che scrive nel file il messaggio corrispondente
        void log(char msg[]);
};