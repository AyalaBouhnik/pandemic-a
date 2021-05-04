#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "OperationsExpert.hpp"


namespace pandemic{

class GeneSplicer:public Player{

private:
	Board b;
	City city;

	public:
	GeneSplicer(Board b, City city):Player(b, city){}	

	void discover_cure(); //can do this action in whatever 5 colors she wants- it dosent needs to be in the same color of the diseas.

};
}
