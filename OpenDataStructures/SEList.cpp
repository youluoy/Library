#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\BNode.cpp"

template<typename T>
class Location{
public:
    BNode<T> *u;
    int j;
    Location() {}
    Location(Node *u, int j){
        this->u = u;
        this->j = j;
    }
    
};

template<typename T>
class SEList{
public:
    int n, b;
    BNode<T> dummy;
    SEList() : dummy(0){
        n = 0;
        b = 0;
    }
    SEList(int c) : dummy(c){
        n = 0;
        b = c;
    }
    void getLocation(int i, Location<T> &ell){
        if(i < n / 2){
            BNode<T> *u = dummy.next;
            while(i >= u->d.size()){
                i -= u->d.size();
                u = u->next;
            }
            ell.u = u;
            ell.j = i;
        }
        else {
            BNode<T> *u = &dummy;
            int idx = n;
            while(i < idx){
                u = u->prev;
                idx -= u->d.size();
            }
            ell.u = u;
            ell.j = i - idx;
        }
    }
    T get(int i){
        Location<T> l;
        getLocation(i, l);
        return l.u->d.get(l.j);
    }
    T set(int i, T x){
        Location<T> l;
        getLocation(i, l);
        T y = l.u->d.get(l.j);
        l.u->d.set(l.j, x);
        return y;
    }
    void add(T x){
        BNode<T> *last = dummy.prev;
        if(last == &dummy || last->d.size() == b+1){
            last = addBefore(&dummy);
        }
        last->d.add(x);
        n++;
    }
    void add(int i, T x){
        if(i == n){
            add(x);
            return;
        }
        Location<T> l;
        getLocation(i, l);
        BNode<T> *u = l.u;
        int r = 0;
        while(r < b && u != &dummy && u->d.size() == b + 1){
            u = u->next;
            r++;
        }
        if(r == b){
            spread(l.u);
            u = l.u;
        }
        if(u == &dummy){
            u = addBefore(u);
        }
        while(u != l.u){
            u->d.add(0, u->prev->d.remove(u->prev->d.size() - 1));
            u = u->prev;
        }
        u->d.add(l.j, x);
        n++;
    }
    T remove(int i){
        Location<T> l;
        getLocation(i, l);
        T y = l.u->d.get(l.j);
        BNode<T> *u = l.u;
        int r = 0;
        while(r < b && u != &dummy && u->d.size() == b - 1){
            u = u->next;
            r++;
        }
        if(r == b){
            gather(l.u);
        }
        u = l.u;
        u->d.remove(l.j);
        while(u->d.size() < b - 1 && u->next != &dummy){
            u->d.add(u->next->d.remove(0));
            u = u->next;
        }
        if(u->d.size() == 0){
            remove(u);
        }
        n--;
        return y;
    }

};