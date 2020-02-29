#include<cassert>
#include<cstddef>
#include"C:\Users\gucch\CompetitivePrograming\library\OpenDataStructures\BDeque.cpp"
template<typename T>
class BNode{
public:
    BDeque<T> d;
    BNode *prev, *next;
    BNode() {}
    BNode(int b) : d(b){ }
};