#include "DisplayMenu.h"
#include "json/json.hpp"
#include <fstream>
#include "tabulate/tabulate.hpp"


using namespace tabulate;
using Row_t = Table::Row_t;


Currency::CurrencyCode DisplayMenu::changeIntToCurrCode(int intToChange)
{
    switch (intToChange)
    {
    case 1:
        return Currency::CurrencyCode::EUR;
        break;
    case 2:
        return Currency::CurrencyCode::USD;
        break;
    case 3:
        return Currency::CurrencyCode::GBP;
        break;
    case 4:
        return Currency::CurrencyCode::CHF;
        break;
    }
}

void DisplayMenu::subMenu(std::string operationType)
{
    int currencyTarget = 0;
    do
    {
        // system("cls");
        std::cout << "Jaka walute chcesz " << operationType << "?" << std::endl;
        std::cout << std::endl;
        std::cout << "1 - EUR" << std::endl;
        std::cout << "2 - USD" << std::endl;
        std::cout << "3 - GBP" << std::endl;
        std::cout << "4 - CHF" << std::endl;
        std::cout << "0 - Wyjdz" << std::endl;
        std::cout << std::endl;

        std::cout << "Co chcesz zrobic?: ";
        std::cin >> currencyTarget;

        if (currencyTarget == 0)
        {
            break;
        }

        Currency::CurrencyCode codeTarget = changeIntToCurrCode(currencyTarget);

        system("cls");

        float amount = 0.0f;

        std::cout << "Podaj ilosc: " << std::endl;
        std::cin >> amount;

        if (operationType == "kupic")
        {
            float bleble = _userRef.buy(codeTarget, amount);
            std::cout << "Do zaplaty  " << bleble << "  PLN. " << std::endl;

        }
        else if (operationType == "sprzedac")
        {
            float blabla = _userRef.sell(codeTarget, amount);
            std::cout << "Wymieniona kwota to: " << blabla << "  PLN. " << std::endl;
        }

    } while (currencyTarget != 0);
}

DisplayMenu::DisplayMenu(User& user)
    : _userRef(user)
{
}

void DisplayMenu::mainMenu()
{
    using json = nlohmann::json;
    json j;


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


    int choice = 0;
    do
    {
        //system("cls");

        std::cout << "**** Witamy w SmartKantor ****" << std::endl << std::endl;
        std::cout << "1 - Kupno" << std::endl;
        std::cout << "2 - Sprzedaz" << std::endl;
        std::cout << "3 - Stan kasy (jeszcze nie wspierany)" << std::endl;
        std::cout << "4 - Aktualizuj kursy (jeszcze nie wspierany)" << std::endl;
        std::cout << "5 - Wyswietl aktualne kursy (jeszcze nie wspierany)" << std::endl;
        std::cout << "0 - Wyjdz" << std::endl;
        std::cout << std::endl;

        std::cout << "Co chcesz zrobic?: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            subMenu("kupic"); //dodawanie koncowki do menu zeby byla tylko jedna funkcja bo dziala tak samo dla kupna/sprzedazy
            break;
        case 2:
            subMenu("sprzedac");
            break;
        case 0:
            std::cout << "Dziekujemy za skorzystanie ze SmartKantor" << std::endl;;
            break;
        }
    } while (choice != 0);
}