// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "curl/curl.h"
#include "json/json.hpp"
#include "tabulate/tabulate.hpp"

#include "currency.hpp"


using namespace tabulate;
using Row_t = Table::Row_t ;

namespace
{
    std::size_t callback(
        const char* in,
        std::size_t size,
        std::size_t num,
        std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

int main()
{
    //const std::string url("http://date.jsontest.com/");
    const std::string url("http://api.nbp.pl/api/exchangerates/tables/c/?format=json");


    CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    long httpCode(0);
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    using json = nlohmann::json;


	if (httpCode == 200)
	{
		std::cout << "\nSuccessful response from NBP " << url << std::endl;
        //std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
       

        //std::cout << std::setw(4) << j;
        std::ofstream o("test.json");
        o << std::setw(4) << *httpData.get() << std::endl;
        json jf = json::parse(*httpData.get());



        std::ifstream ifs("test.json");
        Table table;
        std::vector<Zad::Currency> currency;


        for (auto& el : jf.items())
        {
            nlohmann::json object = el.value();
            std::cout <<"\nGetting trading date: " << object.at("tradingDate") << std::endl;
            std::cout <<"Getting publication date: " << object.at("effectiveDate") << std::endl;
            std::cout <<"  "<< std::endl;
        }

        for (auto& el : jf.items())
		{
			nlohmann::json object = el.value();
			//wyswietla wszyttkie curriencies - all rates
			//std::cout << object.at("rates") << std::endl;

			
			table.add_row(Row_t{ "Currency", "Code", "Buy Price", "Sell Price" });


			for (auto& rate : object.at("rates"))
			{
				//std::cout << rate << std::endl << "***************" << std::endl;
			//wyswietla w osobnym wierszu kazdy rate
				//std::cout << rate << std::endl;

				//std::cout << rate["code"] << "\n";
				//std::cout << rate["currency"] << "\n";
				//std::cout << rate["ask"] << "\n";
				//std::cout << rate["bid"] << "\n";
				//table.add_row(Row_t{ (rate["currency"]), rate["code"], rate["bid"], rate["ask"] }); //-> to jest zla linijka


				
				currency.emplace_back(rate["currency"], rate["code"], rate["ask"], rate["bid"]);
				//currency.push_back(Zad::Currency("Dollar", "USD", 4.9762, 5.0062));
				//currency.emplace_back("Frank szwajcarski", "CHF", 5.0485, 5.0485);
				//currency.emplace_back("Polski zloty", "PLN", 4.5, 4.3);
				//currency.emplace_back("Jen japonski", "JPY", 3.3013, 3.3433);
				//currency.emplace_back("Korona norweska", "NOK", 0.459, 5.5542);

				//std::list<Zad::Currency>currencyList;

				//for (auto& elem : jf["Currency"])
				//{
				//	//std::cout << "Wczytuje " << elem["currencyTarget"];

				//	currencyList.push_back(elem.get<Zad::Currency>());
				//}


				

				//table.add_row(Row_t{ "Currency", "Code", "Buy Price", "Sell Price" });
               

			}

		}
        std::for_each(currency.begin(), currency.end(), [&table](const Zad::Currency& s)
            {

                table.add_row(Row_t{ s.getCurrencyTarget(), s.getCodeName(), std::to_string(s.getBuyPrice()), std::to_string(s.getSellPrice()) });


            });
        std::cout << table << std::endl;
	}
	else
	{
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
	
	}
   
}