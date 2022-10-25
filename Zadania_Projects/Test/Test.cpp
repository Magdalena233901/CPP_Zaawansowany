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
using Row_t = Table::Row_t;

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
		std::ofstream o("currency.json");
		o << std::setw(4) << *httpData.get() << std::endl;
		json jf = json::parse(*httpData.get());



		std::ifstream ifs("currency.json");
		Table table;
		std::vector<Zad::Currency> currency;


		for (auto& el : jf.items())
		{
			nlohmann::json object = el.value();
			std::cout << "\nGetting trading date: " << object.at("tradingDate") << std::endl;
			std::cout << "Getting publication date: " << object.at("effectiveDate") << std::endl;
			std::cout << "  " << std::endl;
		}

		for (auto& el : jf.items())
		{
			nlohmann::json object = el.value();


			table.add_row(Row_t{ "Currency", "Code", "Buy Price", "Sell Price" });


			for (auto& rate : object.at("rates"))
			{
				currency.emplace_back(rate["currency"], rate["code"], rate["ask"], rate["bid"]);
			}

		}
		std::for_each(currency.begin(), currency.end(), [&table](const Zad::Currency& s)
			{

				table.add_row(Row_t{ s.getCurrencyTarget(), s.getCodeName(), std::to_string(s.getBuyPrice()), std::to_string(s.getSellPrice()) });

				//properties of table
				table.column(1).format().width(10);
				table.column(2).format().width(12);
				table.column(3).format().width(12);

				table.format().hide_border_top();
				table.format().corner_top_left("-").corner_bottom_left("-").corner_top_right("-").corner_bottom_right("-");
				table.format().corner_top_right("-");


				//Format header cells
				for (size_t i = 0; i < 4; ++i) {
					table[0][0].format().font_align(FontAlign::center).font_style({ FontStyle::bold }).corner_top_left(".").corner_bottom_left(".");
				}

				// Color header cells - buy price
				for (size_t i = 0; i < 4; ++i) {
					table[0][2].format().font_color(Color::white).font_background_color(Color::red).corner_top_left(".");
				}

				// Color header cells - sell price
				for (size_t i = 0; i < 4; ++i) {
					table[0][3].format().font_color(Color::white).font_background_color(Color::green);
				}


			});
		std::cout << table << std::endl;
	}
	else
	{
		std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;

	}

}