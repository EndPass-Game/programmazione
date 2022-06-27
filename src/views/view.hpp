#include "ncurses.h"
#include "position.hpp"
#include "size.hpp"

class View{
private:

    WINDOW *window; 

public:

    virtual void renderContent();

    virtual void handleInput(char input);
    
    void render();

    void touchAndRender();

    View(Position pos,Size s);

    ~View();
};