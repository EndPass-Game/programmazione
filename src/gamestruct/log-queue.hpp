#pragma once

#include "gamestruct/displayable-string.hpp"
#include "gamestruct/event.hpp"
#include "gamestruct/size.hpp"
#include "datastruct/queue.hpp"

class LogQueue{
private:
    datastruct::Queue<DisplayableString*> *log;
    datastruct::Queue<Event> *eventQueue;
    int lengthLine_;
    int maximumLines_;
    Size paddingTopLeft_;
    
public:
    LogQueue(int lenghtLine_, int maximumLines_,Size paddingTopLeft);
    ~LogQueue();
    void add(Event event);
    void render(WINDOW* win,bool force);
};