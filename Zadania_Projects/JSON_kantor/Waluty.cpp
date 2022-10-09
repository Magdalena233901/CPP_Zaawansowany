#include <iostream>
#include <fstream>
#include "Waluty.hpp"
#include "json/json.hpp"


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

}