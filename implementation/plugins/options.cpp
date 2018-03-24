// embed, a Proposal Implementation

//	The MIT License (MIT)

//	Copyright (c) 2018 ThePhD

//	Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

//	The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "options.hpp"

#include <cstring>

namespace embed {

	options parse(const command_line_arguments& arguments) {
		options opts;
		bool defaulted_local = true;
		for (const auto& key_value : arguments) {
			const std::string_view& key = key_value.first;
			const std::string_view& value = key_value.second;
			if (key == "version" || key == "v") {
				opts.version = true;
				return opts;
			}
			if (key == "help" || key == "h") {
				opts.help = true;
			}
			else if (key == "info" || key == "i") {
				opts.info = true;
			}
			else if (key == "verbose" || key == "v") {
				opts.verbose = true;
			}
			else if (key == "local" || key == "l") {
				defaulted_local = value == "true";
			}
			else if (key == "path" || key == "p") {
				constexpr const auto& delimeter = ";";
				constexpr const auto delimeter_size = (sizeof(delimeter) / sizeof(*delimeter)) - 1;
				const char* first = value.data();
				const char* current = value.data();
				const char* last = first + value.size();
				for (auto pos = value.find(delimeter, 0, delimeter_size); pos != std::string_view::npos; pos = value.find(delimeter, pos, delimeter_size)) {
					std::string::size_type chunksize = (first + pos) - current;
					if (chunksize == 0) {
						continue;
					}
					opts.search_paths.push_back(std::string(current, chunksize));
					pos += delimeter_size;
					current += chunksize;
				}
				if (current != last) {
					opts.search_paths.push_back(std::string(current, last - current));
				}
			}
		}
		if (defaulted_local) {
			opts.search_paths.insert(opts.search_paths.cbegin(), std::string("."));
		}
		return opts;
	}

} // namespace embed
