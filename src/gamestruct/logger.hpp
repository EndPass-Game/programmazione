#pragma once

#include <stdio.h>

// questa classe contiene i metodi che permettono di registrare tutte le azioni avvenute nel gioco all'interno del file di log

class Logger{
  private:
    FILE *fileStream_; // usato per scrivere nel file di log
  public:
    Logger(const char *filename = "game.log", const char *mode = "a");
    ~Logger();

    // funzione che scrive nel file il messaggio corrispondente
    void log(const char *format, ...);
};