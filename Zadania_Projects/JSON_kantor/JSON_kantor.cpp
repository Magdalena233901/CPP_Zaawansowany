// JSON_kantor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Waluty.hpp"

namespace Zad {

    Currency::Currency(std::string newCurrencyTarget, std::string newCodeName, float newBuyPrice, float newSellPrice)
        : currencyTarget(newCurrencyTarget), codeName(newCodeName), buyPrice(newBuyPrice), sellPrice(newSellPrice)
    {};

    void to_json(json& j, const Currency& s)
    {
        j = json{ {"currencyTarget", s.getCurrencyTarget()} , {"codeName" , s.getCodeName()}, {"buyPrice" , s.getBuyPrice()}, {"sellPrice" , s.getSellPrice()} };
    }

    void from_json(const json& j, Currency& s)
    {
        s.setCurrencyTarget(j["currencyTarget"].get<std::string>());
        s.setCodeName(j["codeName"]);

        float buyPrice;
        j["buyPrice"].get_to(buyPrice); //get_to sluzy do porowniania zmiennej
        s.setBuyPrice(buyPrice);

        float sellPrice;
        j["sellPrice"].get_to(sellPrice);
        s.setSellPrice(sellPrice);

    }

}