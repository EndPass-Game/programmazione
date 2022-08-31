#pragma once

#include <ncurses.h>

#include "enums/direction.hpp"
#include "gamestruct/position.hpp"
#include "level/collidable.hpp"
#include "level/displayable-segment.hpp"
#include "level/openable.hpp"
#include "level/segment.hpp"
namespace level {
    class DoorSegment : public DisplayableSegment, public Openable {
      private:
        /**
         * direzione rispetto al centro della stanza in cui si trova la porta
         * usato principalmente per dare consistenza ai cambi di stanza
         * poteva succedere che se uscivi da una porta a destra, rientravi a destra
         * nella prossima stanza, con questi valori, invece se si esce a destra
         * si rientrerà nella possima stanza a sinsitra.
         */
        enums::Direction facingDir_;

        /// -1 default per livello inesistente che non porta a nessun livello
        int nextLevelIdx_;

      public:
        /**
         * @brief Costruisce un nuovo DoorSegment invalido
         */
        DoorSegment();

        /**
         * @brief Costruisce un nuovo DoorSegment
         * 
         * @param segment il segmento portante della porta
         * @param facingDir la direzione rispetto al centro della stanza in cui si trova la porta
         * @param nextLevelIdx il livello collegato a questa porta
         * @param isOpen definisce se la porta è aperta o meno
         */
        DoorSegment(const Segment &segment, enums::Direction facingDir, int nextLevelIdx = -1, bool isOpen = false);

        /**
         * @brief Apre la porta (cambia anche il carattere mostrato)
         */
        void open() override;

        /**
         * @brief chiude la porta (cambia anche il carattere mostrato)
         */
        void close() override;

        /**
         * @brief setter di `nextLevelIdx_`
         * 
         * @param nextLevelIdx l'index del livello collegato alla porta
         */
        void setNextLevelIdx(int nextLevelIdx);

        /**
         * @brief Getter di `nextLevelIdx_`
         * 
         * @return int `nextLevelIdx_`
         */
        int getNextLevelIdx() const;

        /**
         * @brief Getter di `facingDir_`
         * 
         * @return enums::Direction `facingDir_`
         */
        enums::Direction getFacingDir() const;

        /**
         * @returns il tipo di collisione associato a door
         */
        virtual enums::CollisionType getCollisionType() override;
    };
};  // namespace level
