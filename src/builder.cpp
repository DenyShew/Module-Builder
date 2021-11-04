#include "builder.hpp"

builder::builder(const std::string& directory)
{
    this->root_dir = directory;
}

void builder::run()
{
    run_dir(root_dir);
    std::remove((module_dir + "/gcm.cache").c_str());
    std::remove("./gcm.cache");
}

void builder::run_dir(const std::string& directory)
{
    if(!std::filesystem::exists(directory))
    {
        std::cout << "Directory isn't exists, " << directory << std::endl;
    }
    for(auto&& file : std::filesystem::directory_iterator(directory))
    {
        if(file.path().string().find(filename) != std::string::npos)
        {
            parse(file.path().string(), directory);
        }
    }
}

void builder::parse(const std::string& file, const std::string& dir)
{
    std::ifstream in(file);
    if(!in.is_open())
    {
        std::cout << "MBuild file isn't open" << std::endl;
    }
    std::string temp;
    while(std::getline(in, temp))
    {
        if(!temp.find(subdir))
        {
            std::string n_subdir(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            run_dir(dir + "/" + n_subdir);
            continue;
        }
        if(!temp.find(addmod))
        {
            std::string n_mod(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            add_module(n_mod, dir);
            continue;
        }
        if(!temp.find(addbin))
        {
            std::string exec_name(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            add_executable(exec_name, dir);
            continue;
        }
        if(!temp.find(setbin))
        {
            std::string new_bin(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            set_bin(new_bin);
            continue;
        }
        if(!temp.find(setlib))
        {
            std::string new_lib(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            set_lib(new_lib);
            continue;
        }
        if(!temp.find(setmod))
        {\
            std::string new_mod(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            set_module(new_mod);
            continue;
        }
    }
    in.close();
}

void builder::add_executable(const std::string exec_name, const std::string& dir)
{
    int code;
    std::string command = "g++";
    for(auto&& file : std::filesystem::directory_iterator(lib_dir))
    {
        std::string file_name = file.path().string();
        if(file_name.find(".o") != std::string::npos)
        {
            command += " \"" + file_name + "\"";
        }
    }
    command += " -o " + exec_name;
    code = system(command.c_str());
    command = "mv -f  ./" + exec_name + " \"" + binary_dir + "\"";
    code = system(command.c_str());
}

void builder::add_module(const std::string& file, const std::string& dir)
{
    int code;
    if(!std::filesystem::exists(dir + "/gcm.cache"))
    {
        code = system(std::string("ln -s \"" + module_dir + "\"" + " gcm.cache").c_str());
    }
    //TODO: compile add flags
    std::string command = "g++ -c -std=c++20 -fmodules-ts ";
    command += "\"" + dir + "/" + file + "\"";
    code = system(command.c_str());
    std::string module_name;
    for(auto&& file : std::filesystem::directory_iterator("./"))
    {
        std::string file_name = file.path().string();
        if(file_name.find(".o") != std::string::npos)
        {
            code = system(std::string("mv -f " + file_name + "  \"" + lib_dir + "\"").c_str());
            break;
        }
    }
}

void builder::set_bin(const std::string& bin_dir)
{
    if(!std::filesystem::exists(bin_dir))
    {
        std::filesystem::create_directories(bin_dir);
    }
    this->binary_dir = bin_dir;
}

void builder::set_lib(const std::string& lib_dir)
{
    if(!std::filesystem::exists(lib_dir))
    {
        std::filesystem::create_directories(lib_dir);
    }
    this->lib_dir = lib_dir;
}

void builder::set_module(const std::string& module_dir)
{
    if(!std::filesystem::exists(module_dir))
    {
        std::filesystem::create_directories(module_dir + "/gcm.cache");
    }
    this->module_dir = module_dir + "/gcm.cache";
}