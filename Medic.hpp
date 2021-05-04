#include "Player.hpp"


namespace pandemic{
class Medic: public Player{

private:
	Board b;
	City city;
	
	public: 

	Medic(Board b, City city):Player(b, city){}
	Player& treat(City city); //takes down all the diseas-cubes from the city he is standing on(-not just one).
	
	};
	}
