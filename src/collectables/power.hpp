#pragma once

#include "gamestruct/displayable.hpp"
#include "gamestruct/position.hpp"
#include "enums/direction.hpp"
#include "entities/entity.hpp"

class Power: public Displayable, public level::Collidable{
	private:
		
	public:
		//costruttore che inizializza la variabile che definisce l'aumento di vità che darà l'artefatto e la sua posizione
		Power(Position posObj);	

		//override del metodo virtuale per restituire il tipo di oggetto
		virtual enums::CollisionType getCollisionType() override;
		
};