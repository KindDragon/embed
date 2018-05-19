#include <iostream>
#include <string_view>

int main() {
	constexpr std::string_view json_view =
#include "raw_include_data.h"
		;

	std::cout << json_view << std::endl; // Hello, World!
	return 0;
}
