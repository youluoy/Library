#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\Array.cpp"

template<typename T>
class ArrayQueue{
public:
    Array<T> a;
    int j;
    int n;
    void resize(){
        Array<T> b(std::max(2 * n, 1));
        for(int k = 0; k < n; k++){
            b[k] = a[(j + k) % a.size()];
        }
        a = b;
        j = 0;
    }

    ArrayQueue(){
        j = 0;
        n = 0;
    }
    bool add(T x){
        if(n + 1 >= a.size()) resize();
        a[(j + n) % a.size()] = x;
        n++;
        return true;
    }
    T remove(){
        T x = a[j];
        j = (j + 1) % a.size();
        n--;
        if(a.size() >= 3 * n) resize();
        return x;
    }
};