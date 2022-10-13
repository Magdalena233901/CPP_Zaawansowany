// Kolorowanka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
//          foreground background
//black        30         40
//red          31         41
//green        32         42
//yellow       33         43
//blue         34         44
//magenta      35         45
//cyan         36         46
//white        37         47

#include <ostream>
namespace Color {
	enum class Code {
	
		FG_DEFAULT = 39,
		FG_BLACK = 30,
		FG_RED = 31,
		FG_GREEN = 32,
		FG_YELLOW = 33,
		FG_BLUE = 34,
		FG_MAGENTA = 35,
		FG_CYAN = 36,
		FG_LIGHT_GRAY = 37,
		FG_DARK_GRAY = 90,
		FG_LIGHT_RED = 91,
		FG_LIGHT_GREEN = 92,
		FG_LIGHT_YELLOW = 93,
		FG_LIGHT_BLUE = 94,
		FG_LIGHT_MAGENTA = 95,
		FG_LIGHT_CYAN = 96,
		FG_WHITE = 97,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_BLUE = 44,
		BG_DEFAULT = 49
	};

	std::ostream&
		operator<<(std::ostream& os, const Code& code) {
		return os << "\033[" << static_cast<int>(code) << "m";
	}

}


//int main()
//{
//	//\033[ - znak escape 
//	// XX;XX;XX - sekwencja liczb oddzielonych przecinkami
//	// m - oznacza koniec specjlenj sekwencji
//	const std::string red("\033[0;31;42m");
//	const std::string reset("\033[0m");
//
//	std::cout << red << "red text on green background" << reset << std::endl;
//	std::cout << "Bez kolorkow" << std::endl;
//	std::cout << Color::Code::FG_BLUE << Color::Code::BG_RED << "blue text on green background"
//		<< Color::Code::FG_DEFAULT << Color::Code::BG_DEFAULT << std::endl;
//	std::cout << "Bez kolorkow2" << std::endl;
//
//	const std::string test("\033[1;97;42m");
//	std::cout << test << "green text on white background" << reset << std::endl;
//	std::cout << "Bez kolorkow" << std::endl;
//}
