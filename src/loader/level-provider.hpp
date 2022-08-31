#pragma once

#include "datastruct/vector.tpp"
#include "enums/direction.hpp"
#include "gamestruct/logger.hpp"
#include "level/level.hpp"
#include "loader/loader-handler.hpp"

namespace loader {
    /**
     * @brief Singoletto che contiene tutti gli handlers i quali contengono
     * le informazioni per generare un livello
     */
    class LevelProvider {
      private:
        LevelProvider(const char *directory = "assets/");
        datastruct::Vector<LoaderHandler *> loadedLevels_;
        datastruct::Vector<LoaderHandler *> withNorthDoor_;
        datastruct::Vector<LoaderHandler *> withEastDoor_;
        datastruct::Vector<LoaderHandler *> withSouthDoor_;
        datastruct::Vector<LoaderHandler *> withWestDoor_;

        bool hasLoadedLevels_;

        Logger logger_;

        /**
         * @brief funzione helper che ritorna la direzione opposta di quella in input
         * 
         * @param direction la direzione di cui si vuole ottenere una direzione opposta
         * @return enums::Direction la direzione opposta di direction
         */
        enums::Direction _getOppositeDirection(enums::Direction direction);

        /**
         * @brief aggiunge `handler` al vettore corretto
         * 
         * @param handler il loader-handler da aggiungere
         */
        void _dispatchHandler(LoaderHandler *handler);

        /**
         * @brief ritorna il vettore di LoaderHandler corretto in base alla direzione
         * 
         * @param direction la direzione di cui si vuole ottenere il vettore
         * @return datastruct::Vector<LoaderHandler *> il vettore corretto
         */
        datastruct::Vector<LoaderHandler *> *_getLevelVector(enums::Direction direction);

      public:
        /**
         * @returns l'istanza singleton di levelProvider
         */
        static LevelProvider &getInstance();

        /**
         * @brief Elimina la possibilità chiamare il copy constructor il levelProvider
         */
        LevelProvider(const LevelProvider &other) = delete;

        /**
         * @brief Elimina la possibilità di copiare il levelProvider
         */
        LevelProvider &operator=(const LevelProvider &other) = delete;

        /**
         * @brief distruttore della classe LevelProvider
         */
        ~LevelProvider();

        /**
         * @brief carica tutti i livelli di gioco, è possibile chiamarlo una singola
         * volta nel gioco, altrimenti ci saranno duplicati nei vettori di direzione
         */
        void loadLevels();

        /**
         * @param levelIdx l'indice del livello di arrivo, -1 default per dire che non c'è nessun livello
         * @returns un livello con una porta nella direzione desiderata
         */
        level::Level *getLevel(enums::Direction wantedDirection, int levelIdx = -1);
    };
}  // namespace loader
