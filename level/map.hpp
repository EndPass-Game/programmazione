#pragma once 

#include "enums/wall.hpp"
#include "gamestruct/displayable.hpp"

// TODO: questa classe non è necessaria! 
// deve essere messo nei manager dei livelli.
namespace level {
    // questa class è usata come interfaccia per gestire ogni livello
    class Map {
      private: 
        Player *player_; 
        datastruct::Vector<Level *> levels_; // TODO import
        Size currentScreenSize_; // TODO import
      public: 
        Map(Player *player, Size size);
        ~Map();

        // crea un nuovo livello collegato con l'ultimo livello esistente
        Level *newLevel(); 
        // returns the chosen level in in the array (if out of bounds return nullptr)
        Level *getLevel(int index);
    }; 
}; // namespace map