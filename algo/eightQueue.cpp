
#include "common.h"
using namespace dyc;
using namespace std;

class Point {
    int i;
    int j;
};

const int QUEUENUM = 8;

std::vector<Point> point_stack;

vector<vector<int> > solutions;

class IterativeSolve {
public:
    void solve(int qsize) {
        vector<int> points;
        points.reserve(qsize);
        _solve(0, points, qsize);
    }

    bool valid_at(const vector<int>& points, int level, int pos) {
        if (points.size() != level) {
            FATAL("size[%lu] != level[%d]", points.size(), level);
        }
        for (int l=0; l<level; ++l) {
            if (points[l] == pos || abs(l-level) == abs(pos - points[l])) {
                return false;
            }
        }
        return true;
    }

    void _solve(int pos, vector<int>& points, int qsize) {
//        printf("at level %d", pos);
        for (int i=0; i<qsize; ++i) {
            if (valid_at(points, pos, i)) {
                points.push_back(i);
                if (pos+1 < qsize) {
                    _solve(pos+1, points, qsize);
                } else {
 //                   printf("now pos: %d \n", pos);
 //                   int countj = 0;
 //                   for (auto it=points.begin(); it != points.end(); ++it) {
 //                       printf("[%d]: %d \n", countj, points[countj]);
 //                       countj ++;
 //                   }
                    solutions.push_back(points);
 //                   printf("solutions become:%lu \n", solutions.size());
                }
                points.pop_back();
            }
        }
    }
};


int main(int argc, char** argv) {
    int count = QUEUENUM;
    if (argc > 1) {
        count = atoi(argv[1]);
    }
    IterativeSolve solve;
    solve.solve(count);
    printf("%lu solutions\n", solutions.size());
}
