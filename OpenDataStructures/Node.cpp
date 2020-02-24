#include<cassert>
#include<cstddef>

template<typename T>
class Node{
public:
    T x;
    Node *prev;
    Node *next;
    Node(){
        x = 0;
        prev = NULL;
        next = NULL;
    }
    Node(T x0){
        x = x0;
        prev = NULL;
        next = NULL;
    }
};