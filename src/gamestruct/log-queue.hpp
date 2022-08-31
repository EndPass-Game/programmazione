#pragma once

#include "datastruct/queue.tpp"
#include "gamestruct/displayable-string.hpp"
#include "gamestruct/size.hpp"

class LogQueue {
  private:
    datastruct::Queue<DisplayableString *> *log;
    datastruct::Queue<char *> *eventQueue;
    int lengthLine_;
    size_t maximumLines_;
    Size paddingTopLeft_;

  public:
    LogQueue(int lenghtLine_, int maximumLines_, Size paddingTopLeft);
    ~LogQueue();
    void addEvent(char const *event);
    void render(WINDOW *win, bool force);
};