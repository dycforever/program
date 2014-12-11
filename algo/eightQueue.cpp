
#include "common.h"
#include "rawlog.h"

using namespace dyc;
using namespace std;

class Point {
    int i;
    int j;
};

const int QUEUENUM = 8;

std::vector<Point> point_stack;

vector<vector<int> > solutions;

 //                   printf("now pos: %d \n", pos);
 //                   int countj = 0;
 //                   for (auto it=points.begin(); it != points.end(); ++it) {
 //                       printf("[%d]: %d \n", countj, points[countj]);
 //                       countj ++;
 //                   }

class IterativeSolve {
public:
    void solve(int qsize) {
        vector<int> points;
        points.reserve(qsize);
        _solve(points, qsize);
    }

    bool valid_at(const vector<int>& points, int level, int pos) {
        if (points.size() != level) {
            FATAL_LOG("size[%lu] != level[%d]", points.size(), level);
        }
        for (int l=0; l<level; ++l) {
            if (points[l] == pos || abs(l-level) == abs(pos - points[l])) {
                return false;
            }
        }
        return true;
    }

    void _solve(vector<int>& points, int qsize) {
        int candidate = 0;
        while (candidate < qsize || !points.empty()) {
            while(points.size() < qsize) {
                bool found = false;
                for (int i = candidate; i < qsize; i++) {
                    if (valid_at(points, points.size(), i)) {
                        points.push_back(i);
                        found = true;
                        candidate = 0;
                        break;
                    }
                }
                if (!found) {
                    candidate = points[points.size() - 1] + 1;
                    points.pop_back();
                }
                if (candidate >= qsize && points.empty()) {
                    break;
                }
            }
            if (points.size() == qsize) {
                solutions.push_back(points);
                candidate = points[points.size() - 1] + 1;
                points.pop_back();
            }
        }
    }
};

class RecursiveSolve {
public:
    void solve(int qsize) {
        vector<int> points;
        points.reserve(qsize);
        _solve(0, points, qsize);
    }

    bool valid_at(const vector<int>& points, int level, int pos) {
        if (points.size() != level) {
            FATAL_LOG("size[%lu] != level[%d]", points.size(), level);
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

                    solutions.push_back(points);
 //                   printf("solutions become:%lu \n", solutions.size());
                }
                points.pop_back();
            }
        }
    }
};

void check() {
    RecursiveSolve solve1;
    IterativeSolve solve2;
    for (int i = 0; i < 20; i++) {
        solutions.clear();
        solve1.solve(i);
        size_t count1 = solutions.size();

        solutions.clear();
        solve2.solve(i);
        size_t count2 = solutions.size();
        if (count1 != count2) {
            std::cerr << "error! count1 != count2 when i = " << i << std::endl;
            exit(-1);
        }
        std::cout << "pass check " << i << std::endl;
    }
    std::cout << "pass all check!" << std::endl;
}

int main(int argc, char** argv) {
    int count = QUEUENUM;
    if (argc > 1) {
        count = atoi(argv[1]);
    }
    check();
//    printf("%lu solutions\n", solutions.size());
}
