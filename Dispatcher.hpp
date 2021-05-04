#include "Player.hpp"


namespace pandemic{
class Dispatcher: public Player{ 

private:
	Board b;
	City city;

public:
	Dispatcher(Board b,City city):Player(b, city){}
	Player& fly_direct(City city); //can do this action without throwing any suitable card
	};
	}
