// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include < iostream >

int main()
{
	float pln = 0;
	float dollars = 4.99;
	std::cout << " Enter the amount of PLN to convert into USD: " << std::endl;
	std::cin >> pln;
	float converter = (dollars * pln);
	std::cout << " US Dollars : " << converter << std::endl;
	return 0;
}