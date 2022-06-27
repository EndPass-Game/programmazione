#include "ncurses.h"
#include "position.hpp"
#include "size.hpp"

namespace views
{

    class View
    {
    private:
        WINDOW *window;

    public:

        virtual void handleInput(char input);

        virtual void render();

        void touchAndRender();

        View(Position pos, Size s);

        ~View();
    };
};