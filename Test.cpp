
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
#include "doctest.h"

using namespace pandemic;

TEST_CASE("Player actions"){
Board board;  // Initialize an empty board (with 0 disease cubes in any city).

	CHECK(board.is_clean() == true);

	
	board[City::Kinshasa] = 3;      // put 4 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	
	CHECK(board.is_clean() == false);


	Player player {board, City::Atlanta};  // initialize an "operations expert" player on the given board, in Atlanta.
	player.take_card(City::Johannesburg)
	 .take_card(City::Khartoum)
	 .take_card(City::SaoPaulo)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);

	/* role action */
	CHECK(player.role() == "OperationsExpert"); //make sure that the player role is OperationsExpert.


	/* build action */
	CHECK_THROWS(player.build()); // ilegal action: you cant build a research station in Atlanta becuase you dont have this card.
	


	/* drive action */
	player.drive(City::Washington);  // legal action: you drive from Atlanta to a connected city.
	CHECK_THROWS(player.drive(City::Cairo)); // illegal action: you can't drive from Washington to Cairo.
	CHECK_THROWS(player.drive(City::Madrid)); // illegal action: Madrid is not connected to Washington.


	/* fly_direct action */
	player.fly_direct(City::Johannesburg);  // legal action: you discard the Johannesburg card and fly to Johannesburg.
	CHECK_THROWS(player.fly_direct(City::Taipei)); // // illegal action: you do not have the card of Taipei.


	/* treat action */
	player.drive(City::Kinshasa);    // legal action: you move from Johannesburg to a connected city.
	player.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (1 cube remains).
	player.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (0 cubes remain).
	CHECK_THROWS(player.treat(City::Kinshasa)); // illegal action: no more cubes remain in Kinshasa.
	CHECK_THROWS(player.treat(City::Washington));// illegal action: you are not in Washington.


	/* fly_charter action */
	player.drive(City::Khartoum)
	 .fly_charter(City::Sydney);  // legal action: you discard the Khartoum card and fly to Sydney.
	CHECK_THROWS(player.fly_charter(City::Seoul));// illegal action: you do not have the Sydney card (the card of the city you are in).


	/* build action */
	player.drive(City::LosAngeles);  // legal action: note that LosAngeles is connected to Sydney.
	CHECK_THROWS(player.build());     // ilegal action: you do not have the LosAngeles card
	
		
	/* fly_shuttle action */
	player.fly_shuttle(City::Atlanta); // legal action: you fly from one research station to another. 
	player.fly_shuttle(City::LosAngeles); // legal action: you fly from one research station to another.
	CHECK_THROWS(player.fly_shuttle(City::Chicago));// illegal action: there is no research station in Chicago.


	/* discover_cure action */
	CHECK_THROWS(player.discover_cure(Color::Yellow));// // illegal action: you only have 2 yellow cards remaining.

	player.take_card(City::Miami)
	 .take_card(City::Bogota)
	 .take_card(City::Lima);

	player.discover_cure(Color::Yellow); // legal action: you discard 5 yellow cards and discover a yellow cure.
	CHECK_THROWS(player.fly_direct(City::Miami)); // illegal action: you discarded the Miami card to discover a cure, so you cannot use this card.
	CHECK(board.is_clean() == false); // the board is not clean.
	

	/* treat action after discovering a cure */
	player.drive(City::MexicoCity); 
	player.treat(City::MexicoCity);   // you now remove ALL disease cubes from MexicoCity, since there is a yelllow cure.


	/* clean the board */
	CHECK(board.is_clean() == false); // the board is not clean.
	

	player.drive(City::Chicago)
	 .treat(City::Chicago)             // remove one disease cube - there is no blue cure yet.
     .fly_direct(City::HoChiMinhCity)
	 .treat(City::HoChiMinhCity);      // remove one disease cube - there is no red cure yet.

	CHECK(board.is_clean() == true); // the board is not clean. prints "1" - the board is clean - congratulations!!! You treated all diseases!!!
	
	board[City::Kinshasa] = 3;      // put 4 yellow disease cubes in Kinshasa.
	CHECK(board.is_clean() == false); // the board is not clean.

}


TEST_CASE("OperationsExpert player"){
	Board board;  // Initialize an empty board (with 0 disease cubes in any city).

	CHECK(board.is_clean() == true);

	
	board[City::Kinshasa] = 3;      // put 4 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	
	CHECK(board.is_clean() == false);
	

	OperationsExpert player {board, City::Atlanta};  // initialize an "operations expert" player on the given board, in Atlanta.
	player.take_card(City::Johannesburg)
	 .take_card(City::Khartoum)
	 .take_card(City::SaoPaulo)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);

	/* role action */
	CHECK(player.role() == "OperationsExpert"); //make sure that the player role is OperationsExpert.


	/* build action */
	player.build();  // legal action: you build a research station in Atlanta.
		// NOTE: you do not have the Atlanta card, so for other roles this would throw an exception.
		//       But for the OperationsExpert it is legal, since he may build a research station without a card.


	/* drive action */
	player.drive(City::Washington);  // legal action: you drive from Atlanta to a connected city.
	CHECK_THROWS(player.drive(City::Cairo)); // illegal action: you can't drive from Washington to Cairo.
	CHECK_THROWS(player.drive(City::Madrid)); // illegal action: Madrid is not connected to Washington.


	/* fly_direct action */
	player.fly_direct(City::Johannesburg);  // legal action: you discard the Johannesburg card and fly to Johannesburg.
	CHECK_THROWS(player.fly_direct(City::Taipei)); // // illegal action: you do not have the card of Taipei.


	/* treat action */
	player.drive(City::Kinshasa);    // legal action: you move from Johannesburg to a connected city.
	player.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (1 cube remains).
	player.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (0 cubes remain).
	CHECK_THROWS(player.treat(City::Kinshasa)); // illegal action: no more cubes remain in Kinshasa.
	CHECK_THROWS(player.treat(City::Washington));// illegal action: you are not in Washington.


	/* fly_charter action */
	player.drive(City::Khartoum)
	 .fly_charter(City::Sydney);  // legal action: you discard the Khartoum card and fly to Sydney.
	CHECK_THROWS(player.fly_charter(City::Seoul));// illegal action: you do not have the Sydney card (the card of the city you are in).


	/* build action */
	player.drive(City::LosAngeles);  // legal action: note that LosAngeles is connected to Sydney.
	player.build();     // legal action: build a research station in LosAngeles.
		// NOTE: you do not have the LosAngeles card, so for other roles this would throw an exception.
		//       But for the OperationsExpert it is legal, since he may build a research station without a card.
		


	/* fly_shuttle action */
	player.fly_shuttle(City::Atlanta); // legal action: you fly from one research station to another. 
	player.fly_shuttle(City::LosAngeles); // legal action: you fly from one research station to another.
	CHECK_THROWS(player.fly_shuttle(City::Chicago));// illegal action: there is no research station in Chicago.


	/* discover_cure action */
	CHECK_THROWS(player.discover_cure(Color::Yellow));// // illegal action: you only have 2 yellow cards remaining.

	player.take_card(City::Miami)
	 .take_card(City::Bogota)
	 .take_card(City::Lima);

	player.discover_cure(Color::Yellow); // legal action: you discard 5 yellow cards and discover a yellow cure.
	CHECK_THROWS(player.fly_direct(City::Miami)); // illegal action: you discarded the Miami card to discover a cure, so you cannot use this card.
	CHECK(board.is_clean() == false); // the board is not clean.
	

	/* treat action after discovering a cure */
	player.drive(City::MexicoCity); 
	player.treat(City::MexicoCity);   // you now remove ALL disease cubes from MexicoCity, since there is a yelllow cure.


	/* clean the board */
	CHECK(board.is_clean() == false); // the board is not clean.
	

	player.drive(City::Chicago)
	 .treat(City::Chicago)             // remove one disease cube - there is no blue cure yet.
     .fly_direct(City::HoChiMinhCity)
	 .treat(City::HoChiMinhCity);      // remove one disease cube - there is no red cure yet.

	CHECK(board.is_clean() == true); // the board is not clean. prints "1" - the board is clean - congratulations!!! You treated all diseases!!!
	}
	
	
TEST_CASE("Dispatcher player"){
	Board board;  // Initialize an empty board (with 0 disease cubes in any city).

	CHECK(board.is_clean() == true);

	
	board[City::Kinshasa] = 4;      // put 4 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	
	CHECK(board.is_clean() == false);
	

	Dispatcher player {board, City::Atlanta};  // initialize an "Dispatcher" player on the given board, in Atlanta.
	player.take_card(City::Johannesburg)
	 .take_card(City::Khartoum)
	 .take_card(City::SaoPaulo)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);

	/* role action */
	CHECK(player.role() == "Dispatcher"); //make sure that the player role is OperationsExpert.


	/* build action */
	player.build();  // ilegal action: you can't build a research station in Atlanta. becuase you don't have the Atlanta card.


	/* drive action */
	player.drive(City::Washington);  // legal action: you drive from Atlanta to a connected city.
	CHECK_THROWS(player.drive(City::Cairo)); // illegal action: you can't drive from Washington to Cairo.
	CHECK_THROWS(player.drive(City::Madrid)); // illegal action: Madrid is not connected to Washington.


	/* fly_direct action */
	player.fly_direct(City::Johannesburg);  // legal action: you discard the Johannesburg card and fly to Johannesburg.
	CHECK_THROWS(player.fly_direct(City::Taipei)); // illegal action: you do not have the card of Taipei. and there is no resarch statition in Johannesburg.


	/* treat action */
	player.drive(City::Kinshasa);    // legal action: you move from Johannesburg to a connected city.
	player.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (1 cube remains).
	player.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (0 cubes remain).
	CHECK_THROWS(player.treat(City::Kinshasa)); // illegal action: no more cubes remain in Kinshasa.
	CHECK_THROWS(player.treat(City::Washington));// illegal action: you are not in Washington.


	/* fly_charter action */
	player.drive(City::Khartoum);
	CHECK_THROWS(player.fly_charter(City::Seoul));// illegal action: you do not have the Sydney card (the card of the city you are in).


	/* build action */
	player.build(); //you built a station in Khartoum.
		
	CHECK(board.is_clean() == false);
	}
	
	
	
TEST_CASE("Scientist player"){
	Board board;  // Initialize an empty board (with 0 disease cubes in any city).

	CHECK(board.is_clean() == true);

	
	board[City::Kinshasa] = 3;      // put 3 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	
	CHECK(board.is_clean() == false);
	

	Scientist player {board, City::Atlanta ,2};  // initialize an "Scientist" player on the given board, in Atlanta.
	player.take_card(City::Johannesburg)
	 .take_card(City::Khartoum)
	 .take_card(City::SaoPaulo)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);

	/* role action */
	CHECK(player.role() == "Scientist"); //make sure that the player role is Scientist.


	/* drive action */
	player.drive(City::Washington);  // legal action: you drive from Atlanta to a connected city.
	CHECK_THROWS(player.drive(City::Cairo)); // illegal action: you can't drive from Washington to Cairo.
	CHECK_THROWS(player.drive(City::Madrid)); // illegal action: Madrid is not connected to Washington.


	/* fly_direct action */
	player.fly_direct(City::Johannesburg);  // legal action: you discard the Johannesburg card and fly to Johannesburg.
	CHECK_THROWS(player.fly_direct(City::Taipei)); // // illegal action: you do not have the card of Taipei.


	/* treat action */
	player.drive(City::Kinshasa);    // legal action: you move from Johannesburg to a connected city.
	player.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (1 cube remains).
	player.treat(City::Kinshasa);    // legal action: you remove 1 disease cube from current city (0 cubes remain).
	CHECK_THROWS(player.treat(City::Kinshasa)); // illegal action: no more cubes remain in Kinshasa.
	CHECK_THROWS(player.treat(City::Washington));// illegal action: you are not in Washington.


	/* fly_charter action */
	player.drive(City::Khartoum)
	 .fly_charter(City::Sydney);  // legal action: you discard the Khartoum card and fly to Sydney.
	CHECK_THROWS(player.fly_charter(City::Seoul));// illegal action: you do not have the Sydney card (the card of the city you are in).


	player.drive(City::LosAngeles);  // legal action: note that LosAngeles is connected to Sydney.
		


	/* fly_shuttle action */
	player.fly_shuttle(City::Atlanta); // legal action: you fly from one research station to another. 
	player.fly_shuttle(City::LosAngeles); // legal action: you fly from one research station to another.
	CHECK_THROWS(player.fly_shuttle(City::Chicago));// illegal action: there is no research station in Chicago.


	/* discover_cure action */
	CHECK_THROWS(player.discover_cure(Color::Yellow));// // legal action: you have 2 yellow cards remaining, you are Scientist.

	player.take_card(City::Miami)
	 .take_card(City::Bogota)
	 .take_card(City::Lima);
	 
	CHECK(board.is_clean() == false); // the board is not clean. 
	}
	

TEST_CASE("Researcher player"){
	Board board;  // Initialize an empty board (with 0 disease cubes in any city).

	CHECK(board.is_clean() == true);

	
	board[City::Kinshasa] = 5;      // put 5 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	
	CHECK(board.is_clean() == false);
	

	Researcher player {board, City::Atlanta};  // initialize an "Researcher" player on the given board, in Atlanta.
	player.take_card(City::Johannesburg)
	 .take_card(City::Khartoum)
	 .take_card(City::SaoPaulo)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);

	/* role action */
	CHECK(player.role() == "Researcher"); //make sure that the player role is Researcher.


	/* treat action after discovering a cure */
	player.treat(Chicago); //0 disease cube in Chicago.

	}
	
	
	
TEST_CASE("Medic player"){
	Board board;  // Initialize an empty board (with 0 disease cubes in any city).

	CHECK(board.is_clean() == true);

	
	board[City::Kinshasa] = 5;      // put 5 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	
	CHECK(board.is_clean() == false);
	

	Medic player {board, City::Kinshasa};  // initialize an "Medic" player on the given board, in Kinshasa.
	player.take_card(City::Johannesburg)
	 .take_card(City::Khartoum)
	 .take_card(City::MexicoCity)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);

	/* role action */
	CHECK(player.role() == "Medic"); //make sure that the player role is Medic.


	/* treat action */
	player.treat(City::Kinshasa);    // legal action: you remove all the disease cube from current city (0 cube remains).
	CHECK_THROWS(player.treat(City::Kinshasa)); // illegal action: no more cubes remain in Kinshasa.
	CHECK_THROWS(player.treat(City::Washington));// illegal action: you are not in Washington.

	/* discover cure action */
	player.discover_cure(Color::Yellow); // legal action: you discard 5 yellow cards and discover a yellow cure.
	
	CHECK(board.is_clean() == false); // the board is not clean.
	

	/* treat action after discovering a cure */
	player.fly_direct(City::MexicoCity);
	player.treat(City::MexicoCity);   // you now remove ALL disease cubes from MexicoCity, since there is a yelllow cure.
	

	/* clean the board */
	CHECK(board.is_clean() == false); // the board is not clean.

	}
	
	

TEST_CASE("Virologist player"){
	Board board;  // Initialize an empty board (with 0 disease cubes in any city).

	CHECK(board.is_clean() == true);

	
	board[City::Kinshasa] = 3;      // put 3 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	
	CHECK(board.is_clean() == false);
	

	Virologist player {board, City::Atlanta};  // initialize an "Virologist" player on the given board, in Atlanta.
	player.take_card(City::Johannesburg)
	 .take_card(City::Khartoum)
	 .take_card(City::SaoPaulo)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);

	/* role action */
	CHECK(player.role() == "Virologist"); //make sure that the player role is OperationsExpert.


	/* discover_cure action */
	player.discover_cure(Color::Yellow); // legal action, 5 yellow cards and Virologist role.

	CHECK_THROWS(player.treat(City::MexicoCity));   //there is a cure already!

	}
	
	TEST_CASE("GeneSplicer player"){
	Board board;  // Initialize an empty board (with 0 disease cubes in any city).

	CHECK(board.is_clean() == true);

	
	board[City::Kinshasa] = 1;      // put 3 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	
	CHECK(board.is_clean() == false);
	

	GeneSplicer player {board, City::Atlanta};  // initialize an "GeneSplicer" player on the given board, in Atlanta.
	player.take_card(City::Atlanta)
	 .take_card(City::Khartoum)
	 .take_card(City::SaoPaulo)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);

	/* role action */
	CHECK(player.role() == "GeneSplicer"); //make sure that the player role is OperationsExpert.

	/* build action */
	player.build();
	
	/* discover_cure action */
	player.discover_cure(); // you are GeneSplicer so this is a legal action even though you don't have 5 yellow cards .

	CHECK_THROWS(player.treat(City::MexicoCity));   //there is a cure already!

	}
	
	TEST_CASE("FieldDoctor player"){
	Board board;  // Initialize an empty board (with 0 disease cubes in any city).

	CHECK(board.is_clean() == true);

	
	board[City::Kinshasa] = 3;      // put 3 yellow disease cubes in Kinshasa.
	board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
	board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
	board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
	board[City::Chicago] = 1;       // put 1 blue disease cube in Chicago
	
	CHECK(board.is_clean() == false);
	

	FieldDoctor player {board, City::Atlanta};  // initialize an "FieldDoctor" player on the given board, in Atlanta.
	player.take_card(City::Johannesburg)
	 .take_card(City::Khartoum)
	 .take_card(City::SaoPaulo)
	 .take_card(City::BuenosAires)
	 .take_card(City::HoChiMinhCity);

	/* role action */
	CHECK(player.role() == "FieldDoctor"); //make sure that the player role is FieldDoctor.

	/* treat action */
	player.treat(City::Chicago);    // legal action: you remove 1 disease cube from the neighbor current city (1 cube remains).
	CHECK_THROWS(player.treat(City::Chicago)); // illegal action: no more cubes remain in Chicago.
	CHECK_THROWS(player.treat(City::Miami));// illegal action: you are not in Miami neighbor.
	
	/*cheak that you still have the Chicago card*/
	player.fly_direct(City::Chicago);  // legal action: you have the Chicago card and fly to Chicago.
	
	CHECK(board.is_clean() == false); // the board is not clean.
	

	}
