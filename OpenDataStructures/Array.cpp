#include<cassert>
#include<cstddef>
template<typename T>
class Array {
public:
    T *a;
    int length;

    Array(){
        a = NULL;
        length = 0;
    }
    Array(int len){
        length = len;
        a = new T[length];
    }
    T& operator[](int i){
        assert(0 <= i && i < length);
        return a[i];
    }
    Array<T>& operator=(Array<T> &b){
        if(a != NULL)delete[] a;
        a = b.a;
        b.a = NULL;
        length = b.length;
        return *this;
    }
    int size(){
        return length;
    }
};