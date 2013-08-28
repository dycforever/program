#include <common.h>
using namespace std;

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
void convert(T* array, int len, vector<T>& vec){
    for(int i=0; i<len; ++i){
        vec.push_back(i);
    }
}

template<typename T>
void swap(vector<T>& vec, int i, int j){
    T tmp = vec[i];
    vec[i] = vec[j];
    vec[j] = tmp;
}

template<typename T>
void enumerate(vector<T> vec, int line){
//    NOTICE("call emnuerate %d", line);
    if(line == vec.size()-1){
        print(vec);
        return;
    }
    for(int i=line; i<vec.size(); ++i){
        swap(vec, i, line);
        enumerate(vec, line+1); 
        swap(vec, i, line);
    }
}

int main(int argc, char** argv){
    if (argc != 2){
        FATAL("argc must be 2, now: %d", argc);
        return -1;
    }
    int count = atoi(argv[1]);
    int* array = NEW int[count];
    for(int i=0;i<count;++i){
        array[i]=i;
    }
    shuffle_array(array, count);
//    print(array, count);
    vector<int> vec_int;
    convert(array, count, vec_int);
    enumerate(vec_int, 0);
}

