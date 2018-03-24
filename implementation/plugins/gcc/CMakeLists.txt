# embed, a Proposal Implementation

#	The MIT License (MIT)

#	Copyright (c) 2018 ThePhD

#	Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

#	The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.0)

project(embed_plugin_gcc VERSION 0.2.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/lib")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/dbg")
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/dbg")

execute_process(
	COMMAND ${CMAKE_CXX_COMPILER} --print-file-name=plugin
	OUTPUT_VARIABLE compiler_plugin_directory
	ERROR_VARIABLE compiler_plugin_errors
	OUTPUT_STRIP_TRAILING_WHITESPACE
	ERROR_STRIP_TRAILING_WHITESPACE
)

if (compiler_plugin_errors)
	MESSAGE(FATAL_ERROR "[build] There was a problem with finding the compiler plugin directory -- ${compiler_plugin_errors}")
endif(compiler_plugin_errors)

set(embed_plugin_gcc_sources plugin.cpp
	../options.hpp ../options.cpp 
	../feature_test.hpp
	../help.hpp
	../version.hpp
	../api.hpp)
add_library(embed_plugin_gcc SHARED ${embed_plugin_gcc_sources})
target_include_directories(embed_plugin_gcc
	PRIVATE ${compiler_plugin_directory}/include)
target_compile_definitions(embed_plugin_gcc
	PRIVATE EMBED_BUILD)
target_compile_options(embed_plugin_gcc
	PRIVATE -fno-rtti -fPIC)

add_custom_target(check
	ALL
	COMMENT "Running help/info test for embed_plugin_gcc on an empty plugin"
	COMMAND ${CMAKE_CXX_COMPILER} -fplugin=$<TARGET_FILE:embed_plugin_gcc> -fplugin-arg-libembed_plugin_gcc-help -fplugin-arg-libembed_plugin_gcc-info -c -x c++ /dev/null -o /dev/null
	DEPENDS embed_plugin_gcc)