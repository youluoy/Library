#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\Array.cpp"
template<typename T>
class ArrayStack{
private:
    Array<T> a;
    int n;

    void resize(){
        Array<T> b(std::max(2 * n, 1));
        for(int i = 0; i < n; i++){
            b[i] = a[i];
        }
        a = b;
    }
public:
    ArrayStack(){
        n = 0;
    }
    int size(){
        return n;
    }
    T get(int i){
        return a[i];
    }
    T set(int i, T x){
        T y = a[i];
        a[i] = x;
        return y;
    }
    void add(int i, T x){
        if(n + 1 >= a.size()) resize();
        for(int j = n; j > i; j--){
            a[j] = a[j - 1];
        }
        a[i] = x;
        n++;
    }
    T remove(int i){
        T x = a[i];
        for(int j = i; j < n - 1; j++){
            a[j] = a[j + 1];
        }
        n--;
        if(a.size() >= 3 * n) resize();
        return x;
    }
};

