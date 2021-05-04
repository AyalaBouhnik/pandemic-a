#include <iostream>
#include "Player.hpp"

namespace pandemic{

class Researcher: public Player{

private:
	Board b;
	City city;
	
	public:
	Researcher(Board b, City city):Player(b, city){}	

	Player& discovar_cure(); //can do this action in any city- it dosent matter were she is.
	
};
}
