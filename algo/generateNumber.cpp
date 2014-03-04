
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    int num = 15;
    if (argc == 2) {
        num = atoi(argv[1]);
    }
    ofstream fout("data", std::ios::out);
    for (int i=0; i<num; ++i) {
        fout << (random() % 15) - 8 << endl;
    }
}