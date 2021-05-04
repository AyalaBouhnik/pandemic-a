#include <iostream>
#include "Player.hpp"

namespace pandemic{

class Scientist: public Player{

private:
	Board b;
	City city;
	int numbr_of_careds;

public:
	Scientist(Board b, City  city, int numbr_of_careds):Player(b, city){
	numbr_of_careds = numbr_of_careds;
	}	
	Player& discovar_cure(City  city); //can do this action with n cards instead of 5.

};
}
