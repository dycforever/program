#include <common.h>
using namespace std;
using namespace dyc;

template<typename T>
int shuffle_array(T* array, size_t len){
    for(int i=0;i<len;++i){
        int random = rand()%(len-i);
        swap(array[random],array[len-i-1]);
    }
    return 0;
}

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
void print(vector<T>& head){
    for(int i=0; i<head.size(); ++i){
        cout<<head[i]<<" ";
    }
    cout << endl;
}

template<typename T>
void swap(vector<T>& vec, int i, int j){
    T tmp = vec[i];
    vec[i] = vec[j];
    vec[j] = tmp;
}

template<typename T>
bool find(const vector<T>& vec, int start, int end, T target) {
    for (int i=start; i<end; ++i) {
        if (vec[i] == target) {
            return true;
        }
    }
    return false;
}

template<typename T>
void enumerate_in_place(vector<T>& vec, int line){
//    NOTICE("call emnuerate %d", line);
    if(line == vec.size()-1){
        print(vec);
        return;
    }
    for(int i=line; i<vec.size(); ++i){
        if (i != line && vec[i] == vec[line]) {
            continue;
        }
        if (find(vec, line+1, i, vec[i])) {
            continue;
        }

        swap(vec, i, line);
        enumerate_in_place(vec, line+1); 
        swap(vec, i, line);
    }
}



int main(int argc, char** argv){
    int count = 4;
    if (argc == 2){
//        FATAL("argc must be 2, now: %d", argc);
//        return -1;
        count = atoi(argv[1]);
    }
    int* array = NEW int[count];
    for(int i=0;i<count;++i){
        array[i]=i;
    }
    shuffle_array(array, count);
    array[count-1] = 0;
    cout << "======" << endl;
    print(array, count);
    cout << "======" << endl;

    // print in place
    vector<int> vec_int(array, array+count);
    enumerate_in_place(vec_int, 0);
}

