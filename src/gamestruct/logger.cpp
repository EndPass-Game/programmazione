#include "gamestruct/logger.hpp"

#include <cstring>
#include <cstdarg>
#include <cstdio>

using namespace std;


Logger* Logger::instance_=nullptr;
char* Logger::loggerFileName= "game.log";

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
void Logger::log(const char *format, ...){
    va_list args;
    va_start (args, format);
    vfprintf (loggerFile, format, args);
    va_end (args);
}