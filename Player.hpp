#include "Board.hpp"
#include "Color.hpp"
#include "City.hpp"
#include <string>
#pragma once
using namespace pandemic;

namespace pandemic{
class Player{

public:
	City city;
	Board b;
	int num;
public:
	
	Player(Board b1, City city1){
		city1 = city;
		b1 = b;
	}
		Player(Board b1, City city1, int num1){
		city1 = city;
		b1 = b;
		num1 = num;
	}
	
	Player& drive(City city);

	Player& fly_direct(City city);
	
	Player& fly_charter(City city);

	Player& fly_shuttle(City city);

	Player& build();

	Player& discover_cure(Color c); //I need to check if there is resarch station.

	Player& treat(City city);

/////every function needs to update the board and the player station behtaem.

	std::string role(); //this function needs to return the player tafkid.
 
	Player& take_card(City city); //always works!
 
 };
 }
