#include "builder.hpp"

void builder::run()
{
    run_dir(root_dir);
}

void builder::run_dir(const std::string& directory)
{
    for(auto&& file : std::filesystem::directory_iterator(directory))
    {
        if(file.path().string() == filename)
        {
            parse(directory + "/" + file.path().string(), directory);
        }
    }
}

void builder::parse(const std::string& file, const std::string& dir)
{
    std::ifstream in(file);
    std::string temp;
    while(std::getline(in, temp))
    {
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
        if(!temp.find(subdir))
        {
            int start_index = subdir.size() + 1;
            std::string new_dir(temp.begin() + start_index, temp.end());
            run_dir(new_dir);
        }
        if(!temp.find(addmod))
        {
            int start_index = addmod.size() + 1;
            std::string new_mod(temp.begin() + start_index, temp.end());
            add_module(new_mod, dir);
        }
        if(!temp.find(addbin))
        {
            int start_index = addbin.size() + 1;
            std::string new_bin(temp.begin() + start_index, temp.end());
            add_executable(new_bin, dir);
        }
        if(!temp.find(setbin))
        {
            int start_index = setbin.size() + 1;
            std::string new_bin(temp.begin() + start_index, temp.end());
            set_bin(new_bin);
        }
        if(!temp.find(setlib))
        {
            int start_index = setlib.size() + 1;
            std::string new_lib(temp.begin() + start_index, temp.end());
            set_lib(new_lib);
        }
        if(!temp.find(setmod))
        {
            int start_index = setmod.size() + 1;
            std::string new_mod(temp.begin() + start_index, temp.end());
            set_module(new_mod);
        }
    }
}

void add_executable(const std::string exec_name, const std::string file, const std::string& dir, const std::vector<std::string>& params)
{
    std::string command = "g++";
    for(auto&& param : params)
    {
        command += " " + param;
    }
    command += " " + file;
    for(auto&& file : std::filesystem::directory_iterator(lib_dir))
    {
        std::string file_name = file.path().string();
        if(file_name.find(".o") != std::string::npos)
        {
            command += " " + file_name;
        }
    }
    command += " -o " + exec_name;
    system(command.c_str());
    system("mv -f " + dir + "/" + exec_name + " " + binary_dir);
}

void add_module(const std::string& file, const std::string& dir, const std::vector<std::string>& params)
{
    std::string command = "g++ -c -std=c++20 -fmodules-ts";
    for(auto&& param : params)
    {
        command += " " + param;
    }
    command += file;
    system(command.c_str());
    std::string module_name;
    for(auto&& file : std::filesystem::directory_iterator(dir))
    {
        std::string file_name = file.path().string();
        if(file_name.find(".o") != std::string::npos)
        {
            system(std::string("mv -f " + file + " " + lib_dir).c_str());
            break;
        }
    }
    for(auto&& file : std::filesystem::directory_iterator(dir + "gcm.cache"))
    {
        system(std::string("mv -f " + file + " " + module_dir).c_str());
        break;
    }
}