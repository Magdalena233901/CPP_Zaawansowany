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


    json employee = j["company"]["employee"];

    //w json ¿eby dobrac sie do knkretnego elementu trzeba podaæ cala sciezke do tego elementu

    std::string employeeName = employee["name"];
    int salary = employee["payroll"]["salary"];
    int bonus = employee["payroll"]["bonus"];

    int sum = salary + bonus;
    //int sum = employee["payroll"]["salary"].get<int>() + employee["payroll"]["bonus"].get<int>();
    //tutaj mozemy wykonaæ to dzialanie na sztywno podajac typ jaki chcemy dostac

    std::cout << "Zarobki pracownika " << employeeName << " to: " << sum << std::endl;
}

