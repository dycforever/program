
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

std::string filename;

int parseArg(int argc, char** argv) {
    int c;
    while((c = getopt(argc, argv, "f:")) != -1) {
        switch(c) {
            case 'f':
                filename = std::string(optarg);
                break;
            default:
                std::cerr << "parse options failed" << std::endl;
                exit(-1);
        }
    }
} // parseArg()

size_t ReadAndCount(std::istream& in)
{
    std::string line;
    size_t count = 0;
    while (getline(in, line)) {
        ++count;
    }
    return count;
}

int main(int argc, char** argv) {
    parseArg(argc, argv);
    size_t count = 0;
    if (filename == "") {
        count = ReadAndCount(std::cin);
    } else {
        std::ifstream in(filename.c_str());
        count = ReadAndCount(in);
    }

    std::cout << count << std::endl;
}


