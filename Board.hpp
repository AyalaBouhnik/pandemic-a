#include <iostream>
#include <string>
#include "City.hpp"
#pragma once

//using namespace std;
namespace pandemic{

class Board{

public:

	std::string operator[](const City city);
	
	bool is_clean();

	friend std::ostream& operator<<(std::ostream& output, Board b);

};
}
