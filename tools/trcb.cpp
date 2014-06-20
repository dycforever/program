#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const long BUFFERSIZE = 2048;

int main(int argc, char** argv) {
    if (argc != 5) {
        fprintf(stderr, "%d\n", argc);
        fprintf(stderr, "usage: trcb filein start_offset end_offset fileout [)\n");
        return 1;
    }
    char* filein = argv[1];
    long start = strtol (argv[2], NULL, 10);
    long end = strtol (argv[3], NULL, 10);
    char* fileout = argv[4];
    long totalCount = end - start;

    FILE* fin = fopen(filein, "r");
    FILE* fout = fopen(fileout, "w");
    fseek(fin, start, SEEK_SET);
    long off = start;
    char* buf = new char[BUFFERSIZE];

    for (long off = start; off <= end; ++off) {
        long readCount = min(BUFFERSIZE, totalCount);
        if (fread(buf, 1, readCount, fin) != readCount) {
            fprintf(stderr, "read failed");
            return 1;
        }
        totalCount -= readCount;
        if (fwrite(buf, 1, readCount, fout) != readCount) {
            fprintf(stderr, "write failed");
            return 1;
        }
    }
    fclose(fin);
    fclose(fout);
}
