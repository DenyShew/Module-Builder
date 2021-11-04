#ifndef BUILDER_HPP
#define BUILDER_HPP

#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#include <iostream>

class builder
{
public:
    builder(const std::string& directory);

    void run();
private:
    void run_dir(const std::string& directory);
    void parse(const std::string& file, const std::string& dir);

    void add_executable(const std::string exec_name, const std::string& dir);
    void add_module(const std::string& file, const std::string& dir);
    void set_bin(const std::string& bin_dir);
    void set_lib(const std::string& lib_dir);
    void set_module(const std::string& module_dir);
private:
    std::string root_dir;
    std::string binary_dir;
    std::string lib_dir;
    std::string module_dir;

    const std::string filename = "mbuilder.txt";
    const std::string subdir = "subdir";
    const std::string addmod = "add_module";
    const std::string addbin = "add_executable";
    const std::string setbin = "set_binary";
    const std::string setlib = "set_library";
    const std::string setmod = "set_module";
};

#endif//BUILDER_HPP