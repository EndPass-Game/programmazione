#include "gamestruct/log-queue.hpp"

LogQueue::LogQueue(int lengthLine_, int maximumLines_, Size paddingTopLeft)
{
    this->lengthLine_ = lengthLine_;
    this->maximumLines_ = maximumLines_;
    this->paddingTopLeft_ = paddingTopLeft;
    this->log = new datastruct::Queue<DisplayableString*>();
    this->eventQueue = new datastruct::Queue<Event>();
}
LogQueue::~LogQueue(){
    delete this->log;
    delete this->eventQueue;
}

void LogQueue::add(Event event) {
    datastruct::Vector<char*> splitted = stringUtility::splitByLen(event, this->lengthLine_);  
    for(size_t i = 0; i < splitted.size(); i++){
        eventQueue->push((Event)splitted[i]);
    }
    while(eventQueue->size() > this->maximumLines_){
        delete[] eventQueue->pop();
    }
}

void LogQueue::render(WINDOW* win,bool force) {
    bool thereAreEvent=eventQueue->size() > 0;
    if(thereAreEvent){
        for(size_t i = 0; i < log->size(); i++){
            log->at(i)->clearCurrent(win);
        }
        for(size_t i = 0; i < eventQueue->size(); i++){
            Event tmp1 = eventQueue->pop();
            log->push(new DisplayableString({0,0},tmp1));
            delete[] tmp1;
        }
        while(((int)log->size()) > this->maximumLines_){
            delete log->pop();
        }
        for(size_t i = 0; i < log->size(); i++){
            log->at(i)->setPosition({((int) i)+paddingTopLeft_.riga,paddingTopLeft_.colonna});
        }
    }
    for(size_t i = 0; i < log->size(); i++){
        log->at(i)->render(win,force||thereAreEvent);
    } 
}