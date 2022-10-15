#include <iostream>
#include <fstream>
#include <string>
#include "Waluty.hpp"
#include "json/json.hpp"
#include "tabulate.hpp"

using namespace tabulate;
using Row_t = Table::Row_t;

int main()
{
	//get GET https ://v6.exchangerate-api.com/v6/87da24ca90c619102e78ebb3latest/PLN


    using json = nlohmann::json;

    std::vector<Zad::Currency> currency;
    currency.emplace_back("Euro", "EUR", 4.8455, 4.8755);
    currency.push_back(Zad::Currency("Dollar", "USD", 4.9762, 5.0062));
    currency.emplace_back("Frank szwajcarski", "CHF", 5.0485, 5.0485);
    currency.emplace_back("Polski zloty", "PLN", 4.5, 4.3);
	currency.emplace_back("Jen japonski", "JPY", 3.3013, 3.3433);
	currency.emplace_back("Korona norweska", "NOK", 0.459, 5.5542);
    
    json j;

    j["Currency"] = currency;

    //std::cout << std::setw(4) << j;
    std::ofstream o("currency.json");
    o << std::setw(4) << j << std::endl;

    //WCZYTANIE Z PLIKU
	std::ifstream ifs("currency.json");
    json jf = json::parse(ifs);

    std::list<Zad::Currency>currencyList;

    for (auto& elem : jf["Currency"])
    {
        //std::cout << "Wczytuje " << elem["currencyTarget"];

        currencyList.push_back(elem.get<Zad::Currency>());
    }


	Table table;
	table.add_row(Row_t{ "Currency", "Code", "Buy Price", "Sell Price" });
	std::for_each(currencyList.begin(), currencyList.end(), [&table](const Zad::Currency& s)
		{
			
			table.add_row(Row_t{ s.getCurrencyTarget(), s.getCodeName(), std::to_string(s.getBuyPrice()), std::to_string(s.getSellPrice()) });
			//table.add_row(Row_t{ "Euro", "EUR", "4.8455", "4.8755" });


			//Row_t row;
			//row.emplace_back(s.getBuyPrice());
			////to_string			


			// Set width of cells in each column
			//table.column(0).format().width(15); //there is no size, so it's auto
			table.column(1).format().width(10);
			table.column(2).format().width(12);
			table.column(3).format().width(12);

			////Set border sign in the special corner
			//table[1][1].format()
			//	.multi_byte_characters(true).corner_top_left("*").corner_color(Color::yellow);


			//Format header cells
			for (size_t i = 0; i < 4; ++i) {
				table[0][0].format().font_align(FontAlign::center).font_style({ FontStyle::bold });
			}

			// Color header cells - buy price
			for (size_t i = 0; i < 4; ++i) {
				table[0][2].format().font_color(Color::white).font_background_color(Color::red);
			}

			// Color header cells - sell price
			for (size_t i = 0; i < 4; ++i) {
				table[0][3].format().font_color(Color::white).font_background_color(Color::green);
			}

			// Iterator over cells in the third column
			for (auto& cell : table.column(2)) {
				if (cell.get_text() != "Buy Price") {
					cell.format()
						.font_background_color(Color::white).font_color(Color::blue);
				}
			}

			// Iterator over cells in the fourth column
			for (auto& cell : table.column(3)) {
				if (cell.get_text() != "Sell Price") {
					cell.format()
						.font_background_color(Color::white).font_color(Color::blue);
				}
			}
			

			//std::cout << "Currency: " << s.getCurrencyTarget() << "; Code: " << s.getCodeName() << "; Buy Price: " << s.getBuyPrice() << "; Sell Price: " << s.getSellPrice() << std::endl;
		});

	std::cout << table << std::endl;
}