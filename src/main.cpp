// Copyright (c) 2021 nanamedou

#include <string>
#include <locale>
#include <iostream>

#include "kansuji2digit.h"

int main(int argc, char* argv[]){

	str s;
	while (std::cin.good()){
		std::cin >> s;
		k2d::Converter c;
		std::cout << s << "=" << c.kansuji2digit(s.c_str()) << std::endl;
	}
	std::cout << "終わり" << std::endl;

	return 0;
}