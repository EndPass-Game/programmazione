#include "gamestruct/logger.hpp"

#include <cstdarg> // va_list 
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

void Logger::_log(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(fileStream_, format, args);
    va_end(args);
    fprintf(fileStream_, "\n");
    loggerMutex.unlock();
}

void Logger::debug(const char *format, ...) {
#ifdef DEBUG
    loggerMutex.lock();
    fprintf(fileStream_, "[DEBUG] %s: ", loggerName_);
    va_list args;
    _log(format, args);
#endif
}

void Logger::info(const char *format, ...){
    loggerMutex.lock();
    fprintf(fileStream_, "[INFO] %s: ", loggerName_);
    va_list args;
    _log(format, args);
}   

void Logger::warning(const char *format, ...){
    loggerMutex.lock();
    fprintf(fileStream_, "[WARNING] %s: ", loggerName_);
    va_list args;
    _log(format, args);
}

void Logger::error(const char *format, ...){
    loggerMutex.lock();
    fprintf(fileStream_, "[ERROR] %s: ", loggerName_);
    va_list args;
    _log(format, args);
}