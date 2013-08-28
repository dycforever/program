#include "common.h"

using namespace dyc;

std::stack<Point> point_stack;

class Point {
    int i;
    int j;
};

void solve(char[][] plat, int count) {
    int points = NEW int[count];
    
    for (int i=0; i<count; ++i) {
        for (int j=0; j<count; ++j) {

        }
    }
}

int main(int argc, char** argv) {
    int count = 8;
    if (argc > 1) {
        count = atoi(argv[1]);
    }
    char** plat = (char**)NEW int[count * count];
    solve(plat, count);
}
