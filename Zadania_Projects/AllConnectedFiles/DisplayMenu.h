#pragma once
#include <iostream>
#include <string>
#include "Converter.h"

class User  // ta klasy sa tylko na potrzeby dzialania menu,  do usuniecia jak powstanie wlasciwa klasa User
{

    Converter converter1;
public:

    float buy(Currency::CurrencyCode currCodeSource, float amount)
    {
        float value = converter1.calculateBuy(amount, currCodeSource);
        return value;
    }
    float sell(Currency::CurrencyCode currCodeSource, float amount) {
        float value = converter1.calculateSell(amount, currCodeSource);
        return value;
    }
};

class DisplayMenu
{
private:
    User& _userRef;

    Currency::CurrencyCode changeIntToCurrCode(int intToChange);
    void subMenu(std::string operationType);

public:
    DisplayMenu(User& user);
    void mainMenu();
};