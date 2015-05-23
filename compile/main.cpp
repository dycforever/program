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


struct Node {
    std::string mName;
    std::vector<Node> mNode;
};

class Analyser
{
public:
    Analyser() : mPos(0) {}

public:
    void Analyse(const std::string& line);

private:
    bool isAlpha(char c);

private:
    enum {
        TOKEN;
        ARRAY;
        MAP;
    };

private:
    State mState;
    size_t mPos;
    Node mRoot;
};


bool Analyser::isAlpha(char c)
{
    if (c <= 'z' && c >= 'a') {
        return true;
    }
    if (c <= 'Z' && c >= 'A') {
        return true;
    }
    return false;
}

void Analyser::Analyse(const std::string& line, size_t pos, Node& parent)
{
    size_t start = pos;
    for (pos < line.size(); pos++) {
        if (isAlpha(line[pos])) {
            continue;
        } else if (line[pos] == ',') {
            parent.push_back(line.substr(start, pos - start));
        } else if () {
        }
    }
}

size_t ReadAndCount(std::istream& in)
{
    std::string line;
    size_t count = 0;
    while (getline(in, line)) {
        Analyser analyser;
        analyser.Analyse(line);
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

