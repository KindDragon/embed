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

#pragma once

#ifndef EMBED_OPTIONS_HPP
#define EMBED_OPTIONS_HPP

#include "api.hpp"

#include <vector>
#include <filesystem>

namespace embed {

	struct options {
		bool info = false;
		bool help = false;
		bool version = false;
		bool verbose = false;
		std::vector<std::string> search_paths{};
	};

	using command_line_arguments = std::vector<std::pair<std::string_view, std::string_view>>;

	EMBED_API options parse(const command_line_arguments& arguments);

} // namespace embed

#endif // EMBED_OPTIONS_HPP
