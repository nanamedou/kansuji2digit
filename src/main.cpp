// Copyright (c) 2021 nanamedou

#include <string>
#include <locale>
#include <iostream>

#include "kansuji2arabic.h"

int main(int argc, char* argv[]){

	str s;
	while (std::cin.good()){
		std::cin >> s;
		std::cout << s << "=" << kansuji2arabic(s) << std::endl;
	}
	std::cout << "終わり" << std::endl;

	return 0;
}