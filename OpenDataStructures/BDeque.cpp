#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\ArrayDeque.cpp"

template<typename T>
class BDeque : public ArrayDeque<T> {
public:
    BDeque() {
        ArrayDeque<T>::n = 0;
        ArrayDeque<T>::j = 0;
    }
    BDeque(int b){
        ArrayDeque<T>::n = 0;
        ArrayDeque<T>::j = 0;
        Array<int> z(b + 1);
        ArrayDeque<T>::a = z;
    }
    ~BDeque() { }
    void add(int i, T x){
        ArrayDeque<T>::add(i, x);
    }
    bool add(T x){
        ArrayDeque<T>::add(size(), x);
        return true;
    }
    int size(){
        return ArrayDeque<T>::size();
    }
    void resize() {}
};