#pragma once
#pragma once
#include<map>
#include"Currency.h"

class TempRatesRetriever

{
	std::map<Currency::CurrencyCode, Currency> rates;

public: TempRatesRetriever() {
	Currency eur("euro", "EUR", 4.82, 4.91);
	Currency usd("dolar", "USD", 4.99, 5.00);
	Currency gbp("funt", "GBP", 5.53, 5.64);
	Currency chf("frank", "CHF", 4.91, 5.01);
	rates[Currency::CurrencyCode::EUR] = eur;
	rates[Currency::CurrencyCode::USD] = usd;
	rates[Currency::CurrencyCode::GBP] = gbp;
	rates[Currency::CurrencyCode::CHF] = chf;

}

	  std::map<Currency::CurrencyCode, Currency> getRates() {
		  return rates;
	  }

};