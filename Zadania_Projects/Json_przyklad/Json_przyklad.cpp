#include <iostream>
#include <fstream>
#include "json/json.hpp"

using json = nlohmann::json;

int main()
{
	json j;

	j["imie"] = "Magdalena";
	j["nazwisko"] = "Chrobak";
	j["lista"] = {1, 0, 2};
	j["uczelnia"]["PL"] = "student";
	j["praca"]["SiCr"] = "Hardware Verification Engineer";
	j["praca"]["noname"] = "Designer";

	std::ofstream o("me.json");
	o << std::setw(4) << j << std::endl;
}

