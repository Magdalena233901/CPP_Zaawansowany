#include <iostream>
#include <fstream>
#include "json/json.hpp"


using json = nlohmann::json;

int main()
{
	json j;

	j["currency"] = "Dollar";
	j["code"] = "USD";
	j["buy"] = { 4.9762 };
	j["sell"] = { 5.0062 };
	

	std::string jsonString(R"({
    "currency":{ 
      "code":{ 
         "code":"USD",
         "value":{ 
            "buy":4.9762,
            "sell":5.0062
         }
      }
   }
})");

	std::ofstream o("currency.json");
	o << std::setw(4) << j << std::endl;

	json js = json::parse(jsonString);

	std::cout << js["currency"]["code"];

}

