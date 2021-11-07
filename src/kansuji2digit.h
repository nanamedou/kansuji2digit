// Copyright (c) 2021 nanamedou

#include <string>

using str = std::string;
using bytes = const char*;

namespace k2d{

	class Converter{
		str buffer;

	public:
		char const* kansuji2digit(char const* s);
	};
}

