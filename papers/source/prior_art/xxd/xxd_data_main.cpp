#include <iostream>
#include <string_view>

// prefix as constexpr
constexpr
#include "xxd_data.h"
	;

template <typename T, std::size_t N>
constexpr std::size_t array_size(const T (&)[N]) {
	return N;
}

int main() {
	static_assert(xxd_data_bin[0] == 'H');
	static_assert(array_size(xxd_data_bin) == 13);

	std::string_view data_view(reinterpret_cast<const char*>(xxd_data_bin),
		array_size(xxd_data_bin));
	std::cout << data_view << std::endl; // Hello, World!
	return 0;
}
