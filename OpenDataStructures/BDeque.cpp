#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\ArrayDeque.cpp"

template<typename T>
class BDeque : public ArrayDeque<T> {
public:
    BDeque(int b){
        n = 0;
        j = 0;
        Array<int> z(b + 1);
        a = z;
    }
    ~BDeque() { }
    void add(int i, T x){
        ArrayDeque<T>::add(i, x);
    }
    bool add(T x){
        ArrayDeque<T>::add(size(), x);
        return true;
    }
    void resize() {}
};