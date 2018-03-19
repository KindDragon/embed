project(std_embed_gcc VERSION 0.0.1)

cmake_minimum_required(3.2)

set(embed_plugin_sources embed_plugin.cpp)
add_library(embed_plugin SHARED ${embed_plugin_sources})
