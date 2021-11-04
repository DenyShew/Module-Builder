#include "builder.hpp"

builder::builder(const std::string& directory)
{
    this->root_dir = directory;
}

void builder::run()
{
    run_dir(root_dir);
    system("ls -a");
    system(("rm " + module_dir + "/gcm.cache").c_str());
}

void builder::run_dir(const std::string& directory)
{
    std::cout << "Run directory: " << directory << std::endl;
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
    std::cout << "\nMBuild file's name: " << file << std::endl;
    std::ifstream in(file);
    if(!in.is_open())
    {
        std::cout << "MBuild file isn't open" << std::endl;
    }
    std::string temp;
    while(std::getline(in, temp))
    {
        std::cout << "Temp: " << temp << std::endl;
        if(!temp.find(subdir))
        {
            std::string n_subdir(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            std::cout << "Subdir: " << n_subdir << std::endl;
            run_dir(dir + "/" + n_subdir);
            continue;
        }
        if(!temp.find(addmod))
        {
            std::string n_mod(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            std::cout << "Module: " << n_mod << std::endl;
            add_module(n_mod, dir);
            continue;
        }
        if(!temp.find(addbin))
        {
            std::string exec_name(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            std::cout << "Executable: " << exec_name << std::endl;
            add_executable(exec_name, dir);
            continue;
        }
        if(!temp.find(setbin))
        {
            std::string new_bin(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            std::cout << "Set Binary: " << new_bin << std::endl;
            set_bin(new_bin);
            continue;
        }
        if(!temp.find(setlib))
        {
            std::string new_lib(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            std::cout << "Set Library: " << new_lib << std::endl;
            set_lib(new_lib);
            continue;
        }
        if(!temp.find(setmod))
        {\
            std::string new_mod(temp.begin() + temp.find('(') + 1, temp.begin() + temp.find(')'));
            std::cout << "Set Module: " << new_mod << std::endl;
            set_module(new_mod);
            continue;
        }
    }
    in.close();
}

void builder::add_executable(const std::string exec_name, const std::string& dir)
{
    std::cout << "Add executable: " << exec_name << " " << dir << std::endl;
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
    std::cout << "===" << command << std::endl;
    system(command.c_str());
    command = "mv -f  ./" + exec_name + " \"" + binary_dir + "\"";
    std::cout << "===" << command << std::endl;
    system(command.c_str());
}

void builder::add_module(const std::string& file, const std::string& dir)
{
    std::cout << "Add module: " << file << " " << dir << std::endl;
    std::cout << "===ln -s \"" + module_dir + "\" " + "gcm.cache" << std::endl;
    if(!std::filesystem::exists(dir + "/gcm.cache"))
    {
        system(std::string("ln -s \"" + module_dir + "\"" + " gcm.cache").c_str());
    }
    std::string command = "g++ -c -std=c++20 -fmodules-ts ";
    command += "\"" + dir + "/" + file + "\"";
    std::cout << "===" << command << std::endl;
    system(command.c_str());
    std::string module_name;
    for(auto&& file : std::filesystem::directory_iterator("./"))
    {
        std::string file_name = file.path().string();
        if(file_name.find(".o") != std::string::npos)
        {
            std::cout << "===mv -f " + file_name + " " + lib_dir << std::endl;
            system(std::string("mv -f " + file_name + "  \"" + lib_dir + "\"").c_str());
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