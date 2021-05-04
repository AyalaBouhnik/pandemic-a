#include "Player.hpp"


namespace pandemic{
class Virologist: public Player{
 
private:
	Board b;
	City city;
public:
	Virologist(Board b, City city):Player(b, city){}

	Player& treat(City city); //can do this action in any city of the world- it doesnt matter in what city she is.(she need to throw away this city card).

};
}
