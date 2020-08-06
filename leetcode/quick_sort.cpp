#include <iostream>
#include <vector>
#include <random>
#include <tuple>

using namespace std;

void qs(vector<float>& data, size_t start, size_t end) {
    float* dataPtr = data.data();
    if (end <= 1 + start) {
        return;
    }

    if (end == 2 + start) {
        if (data[start] <= data[start + 1]) {
            return;
        }
        swap(data[start], data[start + 1]);
        return;
    }


    size_t lpos = start;
    size_t rpos = end - 1;
    size_t middle = start + (end - start) / 2;
    float pivot = data[middle];

    while (lpos < rpos) {
        while (data[lpos] < pivot && lpos < rpos) {
            lpos++;
        }
        while (data[rpos] > pivot && lpos < rpos) {
            rpos--;
        }
        if (lpos != rpos) {
            swap(data[lpos], data[rpos]);
            lpos++;
        }
    }
    qs(data, start, lpos);
    qs(data, lpos, end);
}

void print(vector<float>& data) {
    for (auto n : data) {
        cout << n << ", ";
    }
    cout << endl;
}

bool checkOrder(vector<float>& data) {
    for (size_t i = 1; i < data.size(); i++) {
        if (data[i] < data[i-1]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::mt19937_64 rng;
    std::uniform_real_distribution<double> unif(0, 1);
    double currentRandomNumber = unif(rng);

    size_t size = 1000;

    vector<float> data(size);
    for (size_t i = 0; i < size; i++) {
        data[i] = int(unif(rng) * 200);
        // data[i] = unif(rng);
    }
    // print(data);
    qs(data, 0, data.size());
    // print(data);
    if (checkOrder(data)) {
        cout << "success\n";
    } else {
        cout << "failed\n";
    }
}

