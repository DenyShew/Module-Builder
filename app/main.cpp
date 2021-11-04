#include "../src/builder.hpp"

int main(int argc, char** argv)
{
    if(argc < 2){
        exit(1);
    }

    builder b(argv[1]);
    b.run();

    return 0;
}