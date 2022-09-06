#pragma once

#include <cstdarg>  // va_list
#include <mutex>
#include <stdio.h>

/**
 * @brief questa classe contiene i metodi che permettono di registrare tutte
 * le azioni avvenute all'interno del gioco in un file di log
 */
class Logger {
  private:
    FILE *fileStream_;        // usato per scrivere nel file di log
    const char *loggerName_;  // nome del l'oggetto da loggare

    void _log(const char *format, va_list args);
    void _headerLog(const char *head, const char *format, va_list args);

  public:
    Logger(const char *loggerName, const char *filename = "game.log", const char *mode = "a");

    ~Logger();

    void debug(const char *format, ...);

    void info(const char *format, ...);

    void warning(const char *format, ...);

    void error(const char *format, ...);
};
