#pragma once
#pragma once
#include <string>
#include "json/json.hpp"

namespace Zad
{
    using json = nlohmann::json;

    class Currency
    {
    public:
        Currency(std::string newCurrencyTarget, std::string newCodeName, float newBuyPrice, float newSellPrice);

        Currency()
        {};

        std::string getCurrencyTarget() const
        {
            return currencyTarget;
        }

        std::string getCodeName() const
        {
            return codeName;
        }

        float getBuyPrice() const
        {
            return buyPrice;
        }

        float getSellPrice() const
        {
            return sellPrice;
        }

        void setCurrencyTarget(std::string newCurrencyTarget)
        {
            currencyTarget = newCurrencyTarget;
        }

        void setCodeName(std::string newCodeName)
        {
            codeName = newCodeName;
        }

        void setBuyPrice(float newBuyPrice)
        {
            buyPrice = newBuyPrice;
        }

        void setSellPrice(float newSellPrice)
        {
            sellPrice = newSellPrice;
        }


    private:
        std::string currencyTarget;
        std::string codeName;
        float buyPrice;
        float sellPrice;
    };

    void to_json(json& j, const Currency& s);
    void from_json(const json& j, Currency& s);

}