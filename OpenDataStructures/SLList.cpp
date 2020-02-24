#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\Node.cpp"

template<typename T>
class SLList{
public:
    Node<T> *head;
    Node<T> *tail;
    int n;


    SLList(){
        head = NULL;
        tail = NULL;
        n = 0;
    }
    T push(T x){
        Node<T> *u = new Node<T>(x);
        u->next = head;
        head = u;
        if(n == 0){
            tail = u;
        }
        n++;
        return x;
    }
    T pop(){
        if(n == 0) return 0;
        T x = head->x;
        Node<T> *u = head;
        head = head->next;
        delete u;
        if(--n == 0) tail = NULL;
        return x;
    }
    bool add(T x){
        Node<T> *u = new Node<T>(x);
        if(n == 0){
            head = u;
        }
        else {
            tail->next = u;
        }
        tail = u;
        n++;
        return true;
    }
    T remove(){
        if(n == 0) return 0;
        T x = head->x;
        Node<T> *u = head;
        head = head->next;
        delete u;
        if(--n == 0) tail = NULL;
        return x;
    }
};