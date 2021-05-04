#include "Board.hpp"
#include "Player.hpp"
#include <string>
using namespace pandemic;

namespace pandemic{


Player& Player::drive(City city){return *this;}

Player& Player::fly_charter(City city){return *this;}

Player& Player::fly_direct(City city){return *this;}

Player& Player::fly_shuttle(City city){return *this;}

Player& Player::build(){return *this;}

Player& Player::discover_cure(Color c){return *this;} //I need to check if there is resarch station.

Player& Player::treat(City city){return *this;}

/////every function needs to update the board and the player station behtaem.

string Player::role(){ // ---this function needs to return the player tafkid.

return "YOU CAN DO IT AYALA!!";

}
 
Player& Player::take_card(City city){return *this;} //always works!
 
 
 }
