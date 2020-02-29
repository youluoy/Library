#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\BNode.cpp"

template<typename T>
class Location{
public:
    BNode<T> *u;
    int j;
    Location() {}
    Location(BNode<T> *u, int j){
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
        dummy.next = &dummy;
        dummy.prev = &dummy;
    }
    SEList(int c) : dummy(c){
        n = 0;
        b = c;
        dummy.next = &dummy;
        dummy.prev = &dummy;
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
    void remove(BNode<T> *w){
        w->prev->next = w->next;
        w->next->prev = w->prev;
        delete w;
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
    BNode<T>* addBefore(BNode<T> *w){
        BNode<T> *u = new BNode<T>(b);
        u->prev = w->prev;
        u->next = w;
        u->next->prev = u;
        u->prev->next = u;
        return u;
    }
    void spread(BNode<T> *u){
        BNode<T> *w = u;
        for(int j = 0; j < b; j++){
            w = w->next;
        }
        w = addBefore(w);
        while(w != u){
            while(w->d.size() < b){
                w->d.add(0, w->prev->d.remove(w->prev->d.size() - 1));
            }
            w = w->prev;
        }
    }
    void gather(BNode<T> *u){
        BNode<T> *w = u;
        for(int j = 0; j < b - 1; j++){
            while(w->d.size() < b){
                w->d.add(w->next->d.remove(0));
            }
            w = w->next;
        }
        remove(w);
    }

};