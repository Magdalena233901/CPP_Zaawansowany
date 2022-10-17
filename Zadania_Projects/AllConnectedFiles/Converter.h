#pragma once
#include<map>
#include "TempRatesRetriever.h"

class Converter
{

	TempRatesRetriever tempRatesRetriever;
public:

	float calculateBuy(float amount, Currency::CurrencyCode currCodeSource)
	{
		std::map<Currency::CurrencyCode, Currency> rates = tempRatesRetriever.getRates();
		float wynik = amount * rates[currCodeSource].getBuyPrice();
		return wynik;

	}
	float calculateSell(float amount, Currency::CurrencyCode currCodeSource)
	{
		std::map<Currency::CurrencyCode, Currency> rates = tempRatesRetriever.getRates();

		float wynik = amount * (1 / (rates[currCodeSource].getSellPrice()));
		return wynik;
	}

};
