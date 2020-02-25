#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\Array.cpp"

template<typename T>
class ArrayDeque{
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

    ArrayDeque(){
        j = 0;
        n = 0;
    }
    T get(int i){
        return a[(j + i) % a.size()];
    }
    T set(int i, T x){
        T y = a[(j + i) % a.size()];
        a[(j + i) % a.size()] = x;
        return y;
    }
    int size(){
        return n;
    }
    void add(int i, T x){
        if(n + 1 >= a.size()) resize();
        if(i < n / 2){
            j = (j == 0) ? a.size() - 1 : j - 1;
            for(int k = 0; k <= i - 1; k++){
                a[(j + k) % a.size()] = a[(j + k + 1) % a.size()];
            }
        }
        else {
            for(int k = n; k > i; k--){
                a[(j + k) % a.size()] = a[(j + k - 1) % a.size()];
            }
        }
        a[(j + i) % a.size()] = x;
        n++;
    }
    T remove(int i){
        T x = a[(j + i) % a.size()];
        if(i < n / 2){
            for(int k = i; k > 0; k--){
                a[(j + k) % a.size()] = a[(j + k - 1) % a.size()];
            }
            j = (j + 1) % a.size();
        }
        else {
            for(int k = i; k < n - 1; k++){
                a[(j + k) % a.size()] = a[(j + k + 1) % a.size()];
            }
        }
        n--;
        if(3 * n < a.size()) resize();
        return x;
    }
};