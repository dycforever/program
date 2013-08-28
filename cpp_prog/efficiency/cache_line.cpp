#include <istream>

#include "common.h"
const long ARRAY_SIZE = 64*1024*1024;

using namespace dyc;
using namespace std;

char arr[ARRAY_SIZE+1024];

void test(char* arr, int K) {
    Timer timer;
    for (int i = 0; i < ARRAY_SIZE; i += K) 
        arr[i] *= 3;
    cout << "step size " << K << " spend:" 
        << timer.microsecond_spend() << " ms" << endl;
}

char* align(char* addr) {
    uint64_t ret = (uint64_t)(addr + 63) & (uint64_t)(~0x3f);
    return (char*)ret;
}

int main(int argc, char** argv) {
//    cout << "arr addr: " << (void*)arr << endl;
    char* array = align(arr);
//    cout << "array addr: " << (void*)array << endl;
    int i = atoi(argv[1]);
    test(array, i);
}


