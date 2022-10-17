#include <iostream>
#include <fstream>
#include "Currency.h"
//#include "json/json.hpp"


Currency::Currency(std::string currencyTarget, std::string codeName, float buyPrice, float sellPrice)
{
	this->currencyTarget = currencyTarget;
	this->codeName = codeName;
	this->buyPrice = buyPrice;
	this->sellPrice = sellPrice;
}

Currency::Currency()
{
}

float Currency::getBuyPrice()
{
	return buyPrice;
}
void Currency::setBuyPrice(float buyPrice)
{
	this->buyPrice = buyPrice;
}
float Currency::getSellPrice()
{
	return sellPrice;
}
void Currency::setSellPrice(float sellPrice)
{
	this->sellPrice = sellPrice;
}
std::string Currency::getCurrencySource()
{
	return currencySource;
}
void Currency::setCurrencySource(std::string currencySource)
{
	this->currencySource = currencySource;
}