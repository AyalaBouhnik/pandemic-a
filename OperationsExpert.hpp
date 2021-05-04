#include <iostream>
#include "Player.hpp"
#pragma once
namespace pandemic{

class OperationsExpert: public Player{

private:
	Board b;
	City city;
	
public:
	OperationsExpert(Board b, City city):Player(b, city){}	



void bulid(); //can do this action without throwing any suitable card

};
}
