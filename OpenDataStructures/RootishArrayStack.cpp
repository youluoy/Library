#include<cassert>
#include<cstddef>
#include<cmath>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\ArrayStack.cpp"

template<typename T>
class RootishArrayStack{
public:
    ArrayStack<T*> blocks;
    int n;
    void grow(){
        blocks.add(blocks.size(), new T[blocks.size() + 1]);
    }
    int i2b(int i){
        double db = (-3.0 + sqrt(9.0 + 8.0 * i)) / 2.0;
        int b = (int)ceil(db);
        return b;
    }

    RootishArrayStack(){
        n = 0;
    }
    T get(int i){
        int b = i2b(i);
        int j = i - b * (b + 1) / 2;
        return blocks.get(b)[j];
    }
    T set(int i, T x){
        int b = i2b(i);
        int j = i - b * (b + 1) / 2;
        T y = blocks.get(b)[j];
        blocks.get(b)[j] = x;
        return y;
    }
    void add(int i, T x){
        int r = blocks.size();
        if(r * (r + 1) / 2 < n + 1)grow();
        n++;
        for(int j = n - 1; j > i; j--){
            set(j, get(j - 1));
        }
        set(i, x);
    }
    T remove(int i){
        T x = get(i);
        for(int j = i; j < n - 1; j++){
            set(j, get(j + 1));
        }
        n--;
        int r = blocks.size();
        if((r - 2) * (r - 1) / 2 >= n){
            shrink();
        }
        return x;
    }
    void shrink(){
        int r = blocks.size();
        while(r > 0 && (r - 2) * (r - 1) / 2 >= n){
            delete [] blocks.remove(blocks.size() - 1);
            r--;
        }
    }
};