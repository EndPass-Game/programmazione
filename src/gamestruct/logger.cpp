#include "gamestruct/logger.hpp"

#include <cstdarg> // va_list 
#include <cstdlib>

Logger::Logger(const char* filename, const char *mode) {
    fileStream_ = fopen(filename, mode);    
    if (fileStream_ == nullptr) {
        fprintf(stderr, "Impossibile aprire il file %s per il log\n", filename);
        exit(1);
    }
}

Logger::~Logger() {
    fclose(fileStream_);
}

void Logger::log(const char *format, ...){
    va_list args;
    va_start(args, format);
    vfprintf (fileStream_, format, args);
    va_end(args);
}