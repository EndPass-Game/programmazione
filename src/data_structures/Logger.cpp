#include "Logger.hpp"

#include <stdio.h>
#include <cstring>
using namespace std;


Logger* Logger::instance_=nullptr;
char* Logger::loggerFileName= strcpy(loggerFileName, "logger.txt");

FILE* Logger::loggerFile=fopen(loggerFileName, "w");

//Costruttore vuoto della classe
Logger::Logger(){}

// crea il singleton o restituisce l'oggetto statico
Logger* Logger::getInstance(){
    if(instance_ == nullptr){
        instance_ = new Logger();
    }
    return instance_;
}
//funzione che scrive nel file il messaggio corrispondente
void Logger::log(char *type, char *msg){
    loggerFile=fopen(loggerFileName, "w");
    fprintf(loggerFile, type, msg);
    fclose(loggerFile);
}