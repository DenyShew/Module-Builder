# Module-Builder

## Проект
Предназначен для упрощения сборки c++20 модулей.
Использует конфигурационные файлы с именами mbuilder.txt.

## Команды в файле
    subdir(name) - Зайти в локальную поддиректорию по ее имени и искать mbuilder.txt.
    
    add_module(name) - Добавить модуль в в проект, в параметр передаются доплнительные
    флаги через пробел и(или) имя файла.
    
    add_executable(name) - Добавить компиляцию исполняемого файла с заданным именем.
    
    set_binary(dir) - Директория, куда будем складывать исполняемые файлы.
    
    set_library(dir) - Директория, куда будем складывать файлы библиотек.
    
    set_module(dir) - Директория, куда будем складывать файлы модулей.
    
## Компиляция
    cd Module-Builder/
    mkdir build
    cd build/
    cmake ..
    cmake --build .
    
## Запуск
    cd Module-Builder/
    cd bin/
    ./Builder <path to directory>
path to directory - корневая директория, где лежит "верхний" mbuilder.txt