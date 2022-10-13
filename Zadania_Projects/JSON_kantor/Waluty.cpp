#include <iostream>
#include <fstream>
#include "Waluty.hpp"
#include "json/json.hpp"
#include "tabulate.hpp"

using namespace tabulate;

int main()
{
    using json = nlohmann::json;

    std::vector<Zad::Currency> currency;
    currency.emplace_back("Euro", "EUR", 4.8455, 4.8755);
    currency.push_back(Zad::Currency("Dollar", "USD", 4.9762, 5.0062));
    currency.emplace_back("Frank szwajcarski", "CHF", 5.0485, 5.0485);
    currency.emplace_back("Funt brytyjski", "GBP", 5.5142, 5.5542);
    
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
        //std::cout << "Wczytuje " << elem["currencyName"];

        currencyList.push_back(elem.get<Zad::Currency>());
    }



    std::for_each(currencyList.begin(), currencyList.end(), [](const Zad::Currency& s) {
        std::cout << "Currency Name: " << s.getCurrencyName() << "; Code: " << s.getCodeName() << "; Buy Price: " << s.getBuyPrice() << "; Sell Price: " << s.getSellPrice() << std::endl; });


    Table table;
    table.add_row({ "Currency", "Code", "Buy Price", "Sell Price" });
    table.add_row({ "Dollar", "USD", "4.9762", "5.0062" });
    table.add_row({ "Euro", "EUR", "4.8455", "4.8755" });


    // Set width of cells in each column
    table.column(0).format().width(10);
    table.column(1).format().width(10);
    table.column(2).format().width(12);
    table.column(3).format().width(12);

    //Set border sign in the special corner
    table[1][1].format()
        .multi_byte_characters(true).corner_top_left("*").corner_color(Color::yellow);
    table.column(1).format()
        .multi_byte_characters(true);



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

    std::cout << table << std::endl;

}