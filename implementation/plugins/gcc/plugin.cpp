// embed, a Proposal Implementation

// The MIT License (MIT)

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

#include "gcc-plugin.h"
#include "plugin-version.h"

#include "../api.hpp"
#include "../options.hpp"
#include "../version.hpp"

#include <iostream>

int plugin_is_GPL_compatible = 1;

namespace embed { namespace gcc {

	void print_plugin_info(struct plugin_name_args* info, struct plugin_gcc_version* version, embed::command_line_arguments& args) {
		std::cerr << "embed, a Proposal Implementation\n";
		std::cerr << "================================\n\n";
		std::cerr << "Base name: " << info->base_name << "\n";
		std::cerr << "Full name: " << info->full_name << "\n";
		std::cerr << "Canonical Author: ThePhD\n";
		std::cerr << "Canonical Implementation: https://github.com/ThePhD/embed\n";

		if (info->version != nullptr) {
			std::cerr << "Version: " << info->version << "\n";
		}

		std::cerr << "\n";
		std::cerr << "GCC Version info\n";
		std::cerr << "================\n\n";
		std::cerr << "Base version: " << version->basever << "\n";
		std::cerr << "Date stamp: " << version->datestamp << "\n";
		std::cerr << "Dev phase: " << version->devphase << "\n";
		std::cerr << "Revision: " << version->devphase << "\n";
		std::cerr << "Configuration arguments: " << version->configuration_arguments << "\n\n";
	}

}} // namespace embed::gcc

int plugin_init(struct plugin_name_args* plugin_info, struct plugin_gcc_version* version) {
	// We check the current gcc loading this plugin against the gcc we used to
	// created this plugin
	if (!plugin_default_version_check(version, &gcc_version)) {
		std::cerr << "This GCC embed plugin is for version " << GCCPLUGIN_VERSION_MAJOR
				<< "." << GCCPLUGIN_VERSION_MINOR << "\n";
		return 1;
	}

	plugin_info->version = embed::version_string.data();
	plugin_info->help = embed::help_text.data();

	bool help_info_exit = false;
	embed::command_line_arguments args;
	args.reserve(plugin_info->argc);

	for (int i = 0; i < plugin_info->argc; i++) {
		std::string_view key = plugin_info->argv[i].key;
		std::string_view value = plugin_info->argv[i].value;
		args.push_back({ key, value });
	}

	embed::options opts = embed::parse(args);

	if (opts.version) {
		std::cerr << embed::version_text << std::endl;
		// must exit immediately after version
		return 0;
	}

	if (opts.help) {
		std::cerr << embed::help_text << std::endl;
		help_info_exit = true;
	}

	if (opts.info) {
		// Print all the things
		embed::gcc::print_plugin_info(plugin_info, version, args);
		help_info_exit = true;
	}

	if (help_info_exit) {
		return 0;
	}

	std::cerr << "embed: initializing...\n";

	std::cerr << "embed: successfully initialized\n";

	return 0;
}
