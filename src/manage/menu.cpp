#include "menu.hpp"

namespace manager
{

    Menu::Menu(){
    }

    void Menu::handleScreenSizeChange(){
    }
   


    void Menu::createWindows() {
        int currentRow=0;
        currentRow += padding;
        asciiArtWin_ = newwin(kAsciiArtSize.x, kAsciiArtSize.y,currentRow,  (COLS - kAsciiArtSize.y) / 2);
        currentRow+=kAsciiArtSize.x;
    }

    Level *Menu::runMenu()
    {
        menuState_=enums::MenuState::RUNNING_MAIN_SCREEN;
        Level *levelManager = new Level();
        clear();
        refresh();
        createWindows();

        for(int i=0;i<kAsciiArtSize.x;i++)
            mvwprintw(asciiArtWin_,i,0,kAsciiArt[i]);

        wrefresh(asciiArtWin_);
        int input_char;
        while (menuState_ != enums::MenuState::FINISH_MENU)
        {
            input_char = getch();
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
        deleteWindows();
        return levelManager;
    }
    void Menu::deleteWindows()
    {
        delwin(asciiArtWin_);
        clear();
    }
}
