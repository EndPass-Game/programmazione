#pragma once

namespace events
{
    class Event
    {
    private:
        char *messaggio;
        int length;
        bool isOnDisplay;
    public:
        Event(char *messaggio, int length, bool isOnDisplay);


    };
}