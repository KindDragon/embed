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

#ifndef EMBED_HELP_HPP
#define EMBED_HELP_HPP

#include "feature_test.hpp"
#include "version.hpp"

#include <string_view>

namespace embed {

#if defined(EMBED_GCC)
	constexpr const std::string_view help_text = R"(embed, a Proposal Implementation
	To use, arguments must passed directly to the GCC invocation with the 
format -fplugin-arg-PLUGIN_NAME-OPTION_NAME[=VALUE], like so:
	-fplugin-arg-libembed_gcc-local=false

The following OPTION_NAMEs/VALUEs options/flags are valid:

-h
-help
	| Display this help and do not initialize plugin.
-i
-info
	| Displays license and plugin information and 
	| do not initialize plugin.
-v
-verbose
	| Display (noisy) diagnostics information
-l[=true]
-local[=true]
	| true/false, default true
	| Whether or not to search the path local to the file.
-p=path/spec/1[;path/spec/2;...]
-path=path/spec/1[;path/spec/2;...]
	| path specification, 1 or more.
	| Semi-colon (';') delimited list of paths, local 
	| or absolute. Multiple path arguments add to the list.
)";
#elif defined(EMBED_CLANG)
	constexpr const std::string_view help_text = R"(embed, a Proposal Implementation)";
#else
	constexpr const std::string_view help_text = R"(embed, a Proposal Implementation)";
#endif

} // namespace embed

#endif // EMBED_HELP_HPP
