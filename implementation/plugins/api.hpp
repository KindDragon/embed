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

#ifndef EMBED_API_HPP
#define EMBED_API_HPP

#include "feature_test.hpp"

#if defined EMBED_VC
#if defined EMBED_DLL
#if defined EMBED_BUILD
#define EMBED_API __declspec(dllexport)
#define EMBED_INTERNAL_API
#else
#define EMBED_API __declspec(dllexport)
#define EMBED_INTERNAL_API
#endif // EMBED_BUILD - Building the Library vs. Using the Library
#else
#define EMBED_API
#define EMBED_INTERNAL_API
#endif // Building a DLL vs. Static Library
#else  // g++ / clang++
#if defined EMBED_BUILD
#define EMBED_API __attribute__((visibility("default")))
#define EMBED_INTERNAL_API __attribute__((visibility("internal")))
#else
#define EMBED_API extern
#define EMBED_INTERNAL_API extern
#endif
#endif // EMBED_BUILD

#endif // EMBED_API_HPP
