#include "gamestruct/logger.hpp"

#include <cstdlib>
#include <mutex>

// mutex per evitare che due thread scrivano contemporaneamente nel file di log
std::mutex loggerMutex; 


Logger::Logger(const char *loggerName, const char *filename, const char *mode) {
    loggerName_ = loggerName;
    fileStream_ = fopen(filename, mode);    
    if (fileStream_ == nullptr) {
        fprintf(stderr, "Impossibile aprire il file %s per il log\n", filename);
        exit(1);
    }
}

Logger::~Logger() {
    fclose(fileStream_);
}

void Logger::_log(const char *format, va_list args) {
    vfprintf(fileStream_, format, args);
    fprintf(fileStream_, "\n");
}

void Logger::_headerLog(const char *head, const char *format, va_list args) {
    loggerMutex.lock();
    fprintf(fileStream_, "%s %s: ", head, loggerName_);
    _log(format, args);
    loggerMutex.unlock();
}

void Logger::debug(const char *format, ...) {
#ifdef DEBUG
    va_list args;
    va_start(args, format);
    _headerLog("[DEBUG]", format, args);
    va_end(args);
#endif
}

void Logger::info(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _headerLog("[INFO]", format, args);
    va_end(args);
}   

void Logger::warning(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _headerLog("[WARNING]", format, args);
    va_end(args);
}

void Logger::error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    _headerLog("[ERROR]", format, args);
    va_end(args);
}