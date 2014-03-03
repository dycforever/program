#include "common.h"
#include <iterator> 

using namespace std;
using namespace dyc;

template<typename T>
void print(vector<T> array) {
    int len = array.size();
    for(int i=0; i<len; ++i){
        cout<<array[i];
        int value = i & 0xf;
        if ( value == 0xf ) {
            cout << endl;
        }else
            cout << " ";
    }
    cout<<endl;
}

template<typename T>
int check(vector<T> array) {
    int len = array.size();
//    NOTICE("begin check array: %p , len: %d", array, len);
    for(int i=0; i<len-1; ++i){
        if ( array[i] > array[i+1] ) {
            FATAL("found erroe array[%d] > array[%d]", i, i+1);
            return -1;
        }
    }
    NOTICE("array is correct in increase");
    return 0;
}

int convert(vector<string>& vec, vector<int>& numbers){
    for(vector<string>::iterator iter = vec.begin();
            iter != vec.end(); ++iter){
        int n = atoi((*iter).c_str()); 
        numbers.push_back(n);
    }
}

int heapsort(int* numbers, int size) {

}

void buildHeap() {
    for (int i=0; i<size; ++i) {
        heapfy(numbers, i+1);
    }
}

void heapfy (int* numbers,int last) {
    int now = last;
    int left = last-1;
    int right = last;
    int top = last/2 - 1;
    while (top > 0) {
        if (numbers[left] > numbers[top]) {
            swap(numbers[left], numbers[top]);
        }
        if (numbers[right] > numbers[top]) {
            swap(numbers[right], numbers[top]);
        }
        last /= 2;
        left = last-1;
        right = last;
        top = last/2 - 1;
    }
}

int quicksort(int* numbers, int size) {
    if( size <= 1){
        return 0;
    }
    int privot = numbers[0];
    int low = 0;
    int high = size;
    while(low < high){
        while ( numbers[--high] > privot && low != high) {
        }

        while ( numbers[++low] <= privot && low != high) {
        }

        if( low < high ){
            swap(numbers[low], numbers[high]);
        }
    }
    swap(numbers[0], numbers[high]);

    quicksort(numbers, high);
    quicksort(numbers+high+1, size-high-1);
}

template<class T>
int uniq(vector<T>& array) {
    size_t size = array.size();
    size_t real = 0;
    for (size_t i=0; i<size; ++i) {
        if (i>0 && array[i] == array[i-1]) {
            continue;
        }
        array[real++] = array[i];
    }
    array.resize(real);
}

int main(){
    string str;
    vector<string> vec;
    while (getline(cin, str, '\n')){
        istringstream iss(str);
        copy(istream_iterator<string>(iss),
                istream_iterator<string>(),
                back_inserter<vector<string> >(vec));
    }
    vector<int> numbers;
    convert(vec, numbers);
    NOTICE("before sort:");
    print(numbers);

    quicksort(numbers.data(), numbers.size());
    NOTICE("after sort:");
    print(numbers);
    check<int>(numbers);

    uniq(numbers);
    print(numbers);
    return 0;
}
