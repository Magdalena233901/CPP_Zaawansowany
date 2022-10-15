#include <iostream>
#include <fstream>
#include "json.hpp"
#include "tabulate.hpp"

using namespace tabulate;
using Row_t = Table::Row_t;

int main()
{
	//get GET https ://v6.exchangerate-api.com/v6/87da24ca90c619102e78ebb3latest/PLN


	using json = nlohmann::json;
	json j;


	//WCZYTANIE Z PLIKU
	////w json ¿eby dobrac sie do knkretnego elementu trzeba podaæ cala sciezke do tego elementu

	std::ifstream ifs("OSTATNI.json");
	json jf = json::parse(ifs);


	Table table;
	table.add_row(Row_t{ "Currency", "Code", "Buy Price", "Sell Price" });
	for (auto& el : jf.items())
	{
		nlohmann::json object = el.value();
		//wyswietla wszyttkie curriencies - all rates
		//std::cout << object.at("rates") << std::endl;

		for (auto& rate : object.at("rates"))
		{
			//std::cout << rate << std::endl << "***************" << std::endl;
		//wyswietla w osobnym wierszu kazdy rate
			//std::cout << rate << std::endl;

			for (const auto& item : object.at("rates"))
			{
				//std::cout << object.at("rates") << "\n";
				for (const auto& val : item.items())
				{
					std::cout << val.key() << ": " << val.value() << "\n";
				}
			}

		}

	}

	std::cout << table << std::endl;
}