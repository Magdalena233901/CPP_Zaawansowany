// Zadanie18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "json/json.hpp"

using json = nlohmann::json;

int main()
{
    std::string jsonString(R"({
    "company":{ 
      "employee":{ 
         "name":"Stefan",
         "payroll":{ 
            "salary":1500,
            "bonus":800
         }
      }
   }
})");


    json j = json::parse(jsonString);

    std::cout << j["company"]["employee"];

}

