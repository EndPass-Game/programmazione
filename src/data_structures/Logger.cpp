#include "Logger.hpp"

#include<fstream>
#include<cstring>
using namespace std;

Logger* Logger::instance_=nullptr;
//Costruttore vuoto della classe
Logger::Logger(): loggerName(strcpy(loggerName, "Logger.txt")){}


Logger* Logger::getInstance(){
    if(instance_ == nullptr){
        instance_ = new Logger();
    }
    return instance_;
}
// crea il singleton o restituisce l'oggetto statico
void Logger::log(char msg[]){
    ofstream fout(loggerName);
    fout<<msg;
    fout.close();
}