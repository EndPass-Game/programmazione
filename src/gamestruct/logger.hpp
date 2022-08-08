#pragma once

#include <stdio.h>
#include <mutex>
// questa classe contiene i metodi che permettono di registrare tutte le azioni avvenute nel gioco all'interno del file di log

class Logger{
  private:
    FILE *fileStream_; // usato per scrivere nel file di log
    const char *loggerName_; // nome del l'oggetto da loggare

    void _log(const char *format, ...); 
  public:
    Logger(const char *loggerName, const char *filename = "game.log", const char *mode = "a");
    ~Logger();

    void debug(const char *format, ...);
    void info(const char *format, ...);
    void warning(const char *format, ...);
    void error(const char *format, ...);
};