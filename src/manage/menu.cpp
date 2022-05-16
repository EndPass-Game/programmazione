#include "menu.hpp"

namespace manager
{

    Menu::Menu() : StackLayout(datastruct::Vector<Size>(windows, 2), 2)
    { }

    void Menu::handleScreenToSmall()
    {
    }

    void Menu::handleResizedScreen()
    {
        for (int i = 0; i <windows[0].x ; i++)
            mvwprintw(getWindow(0)->getWindow(), i, 0, kAsciiArt[i]);
        mvwprintw(getWindow(1)->getWindow(),1,0,"r");
    }

    Level *Menu::runMenu()
    {
        if (!updateScreenSize())
        {
            repaintAll();
        }
        menuState_ = enums::MenuState::RUNNING_MAIN_SCREEN;
        Level *levelManager = new Level();

        int input_char;
        while (menuState_ != enums::MenuState::FINISH_MENU)
        {
            input_char =getch();
            updateScreenSize();
            switch (input_char)
            {
            case 'q':
            {
                menuState_ = enums::MenuState::FINISH_MENU;
                levelManager->gameState->setCurrent(enums::GameState::FINISH);
                break;
            }
            case '\n':
            {
                menuState_ = enums::MenuState::FINISH_MENU;
                levelManager->gameState->setCurrent(enums::GameState::RUNNING);
                break;
            }
            default:
                break;
            }
        }
        //ascii
        //menu
        //quit
        return levelManager;
    }

}
