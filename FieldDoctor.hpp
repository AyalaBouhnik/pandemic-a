#include "Player.hpp"


namespace pandemic{
class FieldDoctor: public Player{ 


private:
	Board b;
	City city;
	
public:
	FieldDoctor(Board b, City city):Player(b ,city){}	
	Player& treat(City n_city); //can do this action in the city he is standing on or in any close city without throwing a city card. 

};
}
