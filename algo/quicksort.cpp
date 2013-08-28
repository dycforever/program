#include "common.h"
#include <iterator> 

using namespace std;

template<typename T>
void print(T* array, int len){
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
int check(T* array, int len){
    NOTICE("begin check array: %p , len: %d", array, len);
    for(int i=0; i<len-1; ++i){
        if ( array[i] > array[i+1] ) {
            FATAL("found erroe array[%d] > array[%d]", i, i+1);
            return -1;
        }
    }
    NOTICE("array is correct in increase");
    return 0;
}

int convert(vector<string>& vec, int* numbers){
    
    int i=0;
    for(vector<string>::iterator iter = vec.begin();
            iter != vec.end(); ++iter){
        int n = atoi((*iter).c_str()); 
        numbers[i] = n;
        ++i;
    }
}

int quicksort(int* numbers, int size){
    if( size <= 1){
        return 0;
    }
    int privot = numbers[0];
    int low = 0;
    int high = size;
    while(low < high){
        while ( numbers[--high] > privot) {
            if (0 == high) {
                break;
            }
        }

        while ( numbers[++low] <= privot) {
            if (low == size) {
                break;
            }
        }

        if( low < high ){
            swap(numbers[low], numbers[high]);
        }
    }
    swap(numbers[0], numbers[high]);

    quicksort(numbers, high);
    quicksort(numbers+high+1, size-high-1);
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
    int* numbers = NEW int[vec.size()];
    convert(vec, numbers);
    NOTICE("before sort:");
//    print<int>(numbers, vec.size());
//    copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, "\n"));
    quicksort(numbers, vec.size());
    NOTICE("after sort:");
    check<int>(numbers, vec.size());
    return 0;
}
