#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\Node.cpp"

template<typename T>
class DLList{
public:
    Node<T> dummy;
    int n;


    DLList(){
        dummy.next = &dummy;
        dummy.prev = &dummy;
        n = 0;
    }
    Node<T>* getNode(int i){
        Node<T> *p;
        if(i < n / 2){
            p = dummy.next;
            for(int j = 0; j < i; j++){
                p = p->next;
            }
        }
        else {
            p = &dummy;
            for(int j = n; j > i; j--){
                p = p->prev;
            }
        }
        return (p);
    }
    T get(int i){
        return getNode(i)->x;
    }
    T set(int i, T x){
        Node<T> *u = getNode(i);
        T y = u->x;
        u->x = x;
        return y;
    }
    Node<T>* addBefore(Node<T> *w, T x){
        Node<T> *u = new Node<T>();
        u->x = x;
        u->prev = w->prev;
        u->next = w;
        u->next->prev = u;
        u->prev->next = u;
        n++;
        return u;
    }
    void add(int i, T x){
        addBefore(getNode(i), x);
    }
    void remove(Node<T> *w){
        w->prev->next = w->next;
        w->next->prev = w->prev;
        delete w;
        n--;
    }
    T remove(int i){
        Node<T> *w = getNode(i);
        T x = w->x;
        remove(w);
        return x;
    }
};