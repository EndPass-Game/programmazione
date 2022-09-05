#pragma once

#include "datastruct/queue.tpp"
#include "gamestruct/displayable-string.hpp"
#include "gamestruct/size.hpp"

/**
 * @brief Classe che contiene e renderizza i messaggi da visualizzare
 * su schermo nell'apposita view
 */
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

    /**
     * @brief aggiunge un evento, ossia una stringa rappresentante un fatto
     * nel gioco, da mostrare su schermo
     */
    void addEvent(char const *event);

    void render(WINDOW *win, bool force);
};