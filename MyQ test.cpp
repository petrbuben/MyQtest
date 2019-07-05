// MyQ test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "nlohmann/json.hpp"
//#include "MyQ test.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>

// for convenience
using json = nlohmann::json;

void endWrite(char*);
void backOff(char*);
void turnR(char*);
void turnL(char*);
void adv(char*);
void cln(char*);
int BOadv(char*);
int BObck(char*);

namespace myq {
	/*struct info {
		std::vector<std::vector<std::string>> map;
		std::map<std::string, std::string> start;
		std::vector<std::string> commands;
		int battery;
	};
	*/

}
json j;
json jout;
int x = 0, y = 0;
std::map<std::string, int> mvisited;
std::vector<std::map<std::string, int> > vecmvisited;
//jout["visited"] = vecmvisited;

std::map<std::string, int> mcleaned;
std::vector<std::map<std::string, int> > vecmcleaned;
//jout["cleaned"] = vecmcleaned;



int main(int argc, char* argv[])
{
	// read a JSON file
//	std::ifstream i("test1.json");
	std::ifstream i(argv[1]);

//	std::cout << argv[1]<<std::endl;

	//json j;
	i >> j;
	
	//json jout;
	//all cells visited
	x = j["start"]["X"];
	y = j["start"]["Y"];

//jout["visited"] = { {{"X", vx}, {"Y", vy}}, {{"X", 5}, {"Y", 6}} };
	
	

	mvisited.insert(std::pair<std::string, int>("X", x));
	mvisited.insert(std::pair<std::string, int>("Y", y));
	vecmvisited.push_back(mvisited);
	mvisited.clear();
	jout["visited"] = vecmvisited;

	jout["cleaned"] = vecmcleaned;

	/*
	mvisited.insert(std::pair<std::string, int>("X", 111));
	mvisited.insert(std::pair<std::string, int>("Y", 222));
	vecmvisited.push_back(mvisited);
	mvisited.clear();
	
	
	mcleaned.insert(std::pair<std::string, int>("X", 88));
	mcleaned.insert(std::pair<std::string, int>("Y", y));
	vecmcleaned.push_back(mcleaned);
	mcleaned.clear();
	jout["cleaned"] = vecmcleaned;

	mcleaned.insert(std::pair<std::string, int>("X", 99));
	mcleaned.insert(std::pair<std::string, int>("Y", y));
	vecmcleaned.push_back(mcleaned);
	mcleaned.clear();
	jout["cleaned"] = vecmcleaned;
	*/
	//jout["visited"].push_back(std::map<std::pair<std::string, int>("Xx", 55));
	//jout["visited"].push_back(std::pair<std::string, int>("Xx", 55), std::pair<std::string, int>("Yy", 66));
	//jout["visited"] = json::array({ {},{} });
	//jout["visited"] = { {} };
	//all cells cleaned
	//jout["cleaned"] = json::array({ {}, {} });
	//final position
	//jout["finalpos"] = { {"X", "0"}, {"Y", "0"}, {"facing", "0"} };
	jout["final"] = j["start"];
	//battery
	jout["battery"] = j["battery"];
	
	/*
	std::cout << j["battery"]<<std::endl;
	std::cout << j["commands"][0];
	std::cout << j["commands"].at(1);
	std::cout << j["start"]["X"];
	std::cout << j["start"].at("Y");
	std::cout << j["map"][3][1];
	//myq::info in;
	*/
	//std::cout << jout["final"]["X"];
	//std::cout << std::endl;
	
	//check battery
	if (jout["battery"] < 1)
		endWrite(argv[2]);
	
	//cist commands
	for (auto itr = j["commands"].begin(); itr != j["commands"].end(); itr++) {
		std::cout << *itr<<" ";
		//execute commands
		if (*itr == "TL") {
			//std::cout << "***TL" << " ";
			turnL(argv[2]);

			/*
			if (jout["battery"] < 1)
				endWrite(argv[2]);

			if (jout["final"]["facing"] == "N")
				jout["final"]["facing"] = "W";
			else if(jout["final"]["facing"] == "W")
				jout["final"]["facing"] = "S";
			else if (jout["final"]["facing"] == "S")
				jout["final"]["facing"] = "E";
			else if (jout["final"]["facing"] == "E")
				jout["final"]["facing"] = "N";

			jout["battery"] = jout["battery"] - 1;
			if (jout["battery"] == 0)
				endWrite(argv[2]);
			*/
		}
		else if (*itr == "TR") {
			//std::cout << "***TR" << " ";
			turnR(argv[2]);
			/*
			if (jout["battery"] < 1)
				endWrite(argv[2], jout);

			if (jout["final"]["facing"] == "N")
				jout["final"]["facing"] = "E";
			else if (jout["final"]["facing"] == "E")
				jout["final"]["facing"] = "S";
			else if (jout["final"]["facing"] == "S")
				jout["final"]["facing"] = "W";
			else if (jout["final"]["facing"] == "W")
				jout["final"]["facing"] = "N";

			jout["battery"] = jout["battery"] - 1;
			if (jout["battery"] == 0)
				endWrite(argv[2], jout);
		*/
		}
		
		//aaaaaaaaaaaaaaaaa
		else if (*itr == "A") {
			adv(argv[2]);
			/*
			if (jout["battery"] < 2)
				endWrite(argv[2]);
			//int x = 0, y = 0;
			if (jout["final"]["facing"] == "N") {
				//jout["finalpos"]["Y"] = jout["finalpos"]["Y"] - 1;
				x = jout["final"]["X"] - 1;
			}
			else if (jout["final"]["facing"] == "S") {
				//jout["finalpos"]["Y"] = jout["finalpos"]["Y"] + 1;
				x = jout["final"]["X"] + 1;
			}
			else if (jout["final"]["facing"] == "E") {
				//jout["finalpos"]["X"] = jout["finalpos"]["X"] + 1;
				y = jout["final"]["Y"] + 1;
			}
			else if (jout["final"]["facing"] == "W") {
				//jout["finalpos"]["X"] = jout["finalpos"]["X"] - 1;
				y = jout["final"]["Y"] - 1;
			}

			if (x < 0 || y < 0 || j["map"][x][y] != "S")
				backOff();
			else
			{
				jout["final"]["X"] = x;
				jout["final"]["Y"] = y;

				//jout["visited"]
				mvisited.insert(std::pair<std::string, int>("X", x));
				mvisited.insert(std::pair<std::string, int>("Y", y));
				vecmvisited.push_back(mvisited);
				mvisited.clear();
				jout["visited"] = vecmvisited;

				jout["battery"] = jout["battery"] - 2;
				if (jout["battery"] == 0)
					endWrite(argv[2]);
			}//no backoff
			*/
		}
		//cccccccccccccccccccc
		else if (*itr == "C") {
			cln(argv[2]);
			/*
			if (jout["battery"] < 5)
				endWrite(argv[2]);
			
			//int x = jout["final"]["X"];
			//int y = jout["final"]["Y"];
			//jout["cleaned"]
			mcleaned.insert(std::pair<std::string, int>("X", jout["final"]["X"]));
			mcleaned.insert(std::pair<std::string, int>("Y", jout["final"]["Y"]));
			vecmcleaned.push_back(mcleaned);
			mcleaned.clear();
			jout["cleaned"] = vecmcleaned;

			jout["battery"] = jout["battery"] - 5;
			if (jout["battery"] == 0)
				endWrite(argv[2]);
			*/
		}

		else if (*itr == "B") {
			exit(1);
		}
	} //for commands read
	
	
	
	/*
	// write prettified JSON to another file
	std::ofstream o(argv[2]);
	o << std::setw(2) << jout << std::endl; 
	*/
	endWrite(argv[2]);
} //main

void endWrite(char* a) {
	// write prettified JSON to another file
	std::ofstream o(a);
	o << std::setw(2) << jout << std::endl;
	exit(0);
}

void turnR(char* a) {
	if (jout["battery"] < 1)
		endWrite(a);

	if (jout["final"]["facing"] == "N")
		jout["final"]["facing"] = "E";
	else if (jout["final"]["facing"] == "E")
		jout["final"]["facing"] = "S";
	else if (jout["final"]["facing"] == "S")
		jout["final"]["facing"] = "W";
	else if (jout["final"]["facing"] == "W")
		jout["final"]["facing"] = "N";

	jout["battery"] = jout["battery"] - 1;
	if (jout["battery"] == 0)
		//endWrite(argv[2], jout);
		endWrite(a);
}

void turnL(char* a) {
	if (jout["battery"] < 1)
		endWrite(a);

	if (jout["final"]["facing"] == "N")
		jout["final"]["facing"] = "W";
	else if (jout["final"]["facing"] == "W")
		jout["final"]["facing"] = "S";
	else if (jout["final"]["facing"] == "S")
		jout["final"]["facing"] = "E";
	else if (jout["final"]["facing"] == "E")
		jout["final"]["facing"] = "N";

	jout["battery"] = jout["battery"] - 1;
	if (jout["battery"] == 0)
		endWrite(a);
}

void adv(char* a) {
	if (jout["battery"] < 2)
		endWrite(a);
	//int x = 0, y = 0;
	if (jout["final"]["facing"] == "N") {
		//jout["finalpos"]["Y"] = jout["finalpos"]["Y"] - 1;
		x = jout["final"]["X"] - 1;
	}
	else if (jout["final"]["facing"] == "S") {
		//jout["finalpos"]["Y"] = jout["finalpos"]["Y"] + 1;
		x = jout["final"]["X"] + 1;
	}
	else if (jout["final"]["facing"] == "E") {
		//jout["finalpos"]["X"] = jout["finalpos"]["X"] + 1;
		y = jout["final"]["Y"] + 1;
	}
	else if (jout["final"]["facing"] == "W") {
		//jout["finalpos"]["X"] = jout["finalpos"]["X"] - 1;
		y = jout["final"]["Y"] - 1;
	}

	if (x < 0 || y < 0 || j["map"][x][y] != "S")
		backOff(a);
	
	jout["final"]["X"] = x;
	jout["final"]["Y"] = y;

	//jout["visited"]
	mvisited.insert(std::pair<std::string, int>("X", x));
	mvisited.insert(std::pair<std::string, int>("Y", y));
	vecmvisited.push_back(mvisited);
	mvisited.clear();
	jout["visited"] = vecmvisited;

	jout["battery"] = jout["battery"] - 2;
	if (jout["battery"] == 0)
		endWrite(a);
}

void cln(char* a) {
	if (jout["battery"] < 5)
		endWrite(a);
	//jout["cleaned"]
	mcleaned.insert(std::pair<std::string, int>("X", jout["final"]["X"]));
	mcleaned.insert(std::pair<std::string, int>("Y", jout["final"]["Y"]));
	vecmcleaned.push_back(mcleaned);
	mcleaned.clear();
	jout["cleaned"] = vecmcleaned;

	jout["battery"] = jout["battery"] - 5;
	if (jout["battery"] == 0)
		endWrite(a);
}

void backOff(char*a) {
	if (jout["battery"] < 3)
		endWrite(a);
	//1
	turnR(a);
	//adv
	if (BOadv(a)) 
		return;
	//2
	turnL(a);
	if (BObck(a))
		return;
	turnR(a);
	if (BOadv(a))
		return;
	//3
	turnL(a);
	turnL(a);
	if (BOadv(a))
		return;
	//4
	turnR(a);
	if (BObck(a))
		return;
	turnR(a);
	if (BOadv(a))
		return;
	//5
	turnL(a);
	turnL(a);
	if (BOadv(a))
		return;
	//6
	endWrite(a);
}


int BOadv(char* a) {
	if (jout["battery"] < 2)
		endWrite(a);
	//int x = 0, y = 0;
	if (jout["final"]["facing"] == "N") {
		//jout["finalpos"]["Y"] = jout["finalpos"]["Y"] - 1;
		x = jout["final"]["X"] - 1;
	}
	else if (jout["final"]["facing"] == "S") {
		//jout["finalpos"]["Y"] = jout["finalpos"]["Y"] + 1;
		x = jout["final"]["X"] + 1;
	}
	else if (jout["final"]["facing"] == "E") {
		//jout["finalpos"]["X"] = jout["finalpos"]["X"] + 1;
		y = jout["final"]["Y"] + 1;
	}
	else if (jout["final"]["facing"] == "W") {
		//jout["finalpos"]["X"] = jout["finalpos"]["X"] - 1;
		y = jout["final"]["Y"] - 1;
	}

	//no more bo - return to write and proceed
	if (x >= 0 && y >= 0 && j["map"][x][y] == "S")
		//additional 1
		//jout["battery"] = jout["battery"] - 1;
		return 1;
	else
	{
		//nejde - nove bo
		x = jout["final"]["X"];
		y = jout["final"]["Y"];
		return 0;
	}
}//Boadv


int BObck(char* a) {
	if (jout["battery"] < 3)
		endWrite(a);
	//int x = 0, y = 0;
	if (jout["final"]["facing"] == "N") {
		//jout["finalpos"]["Y"] = jout["finalpos"]["Y"] - 1;
		x = jout["final"]["X"] + 1;
	}
	else if (jout["final"]["facing"] == "S") {
		//jout["finalpos"]["Y"] = jout["finalpos"]["Y"] + 1;
		x = jout["final"]["X"] - 1;
	}
	else if (jout["final"]["facing"] == "E") {
		//jout["finalpos"]["X"] = jout["finalpos"]["X"] + 1;
		y = jout["final"]["Y"] - 1;
	}
	else if (jout["final"]["facing"] == "W") {
		//jout["finalpos"]["X"] = jout["finalpos"]["X"] - 1;
		y = jout["final"]["Y"] + 1;
	}

	//no more bo - return to write and proceed
	if (x >= 0 && y >= 0 && j["map"][x][y] == "S") {
		//additional 1
		jout["battery"] = jout["battery"] - 1;
		return 1;
	}
	else
	{
		//nejde - nove bo
		x = jout["final"]["X"];
		y = jout["final"]["Y"];
		return 0;
	}
}//BObck