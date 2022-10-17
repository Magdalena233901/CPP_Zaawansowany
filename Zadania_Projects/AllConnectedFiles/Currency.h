#pragma once
#include<string>
//#include "json/json.hpp"


class Currency
{
	std::string currencyTarget;
	std::string codeName;
	float buyPrice;
	float sellPrice;
	std::string currencySource = "PLN";//czyli PLN
public:
	Currency(std::string currencyTarget, std::string codeName, float buyPrice, float sellPrice);
	Currency();
	enum class CurrencyCode
	{
		EUR, USD, GBP, CHF, PLN
	};
	float getBuyPrice();
	void setBuyPrice(float newBuyPrice);
	float getSellPrice();
	void setSellPrice(float newSellPrice);
	std::string getCurrencySource();
	void setCurrencySource(std::string currencySource);
	//void to_json(json& j, const Currency& s);
	//void from_json(const json& j, Currency& s);
};
