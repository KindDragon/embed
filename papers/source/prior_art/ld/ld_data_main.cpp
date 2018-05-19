#include <iostream>
#include <string_view>

#ifdef __APPLE__
#include <mach-o/getsect.h>

#define DECLARE_LD(NAME) extern const unsigned char _section$__DATA__##NAME[];
#define LD_NAME(NAME) _section$__DATA__##NAME
#define LD_SIZE(NAME) (getsectbyname("__DATA", "__" #NAME)->size)

#elif (defined __MINGW32__) /* mingw */

#define DECLARE_LD(NAME)                                 \
	extern const unsigned char binary_##NAME##_start[]; \
	extern const unsigned char binary_##NAME##_end[];
#define LD_NAME(NAME) binary_##NAME##_start
#define LD_SIZE(NAME) ((binary_##NAME##_end) - (binary_##NAME##_start))

#else /* gnu/linux ld */

#define DECLARE_LD(NAME)                                  \
	extern const unsigned char _binary_##NAME##_start[]; \
	extern const unsigned char _binary_##NAME##_end[];
#define LD_NAME(NAME) _binary_##NAME##_start
#define LD_SIZE(NAME) ((_binary_##NAME##_end) - (_binary_##NAME##_start))
#endif

DECLARE_LD(ld_data_bin);

int main() {
	// impossible
	//static_assert(xxd_data_bin[0] == 'H');
	std::string_view data_view(reinterpret_cast<const char*>(LD_NAME(ld_data_bin)), LD_SIZE(ld_data_bin));
	std::cout << data_view << std::endl; // Hello, World!
	return 0;
}
