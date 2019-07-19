#include<bits/stdc++.h>
using namespace std;

template<typename T> class LazySegmentTree {
    int n, sz;
    vector<T> dat, Lazy;
    const T INF = numeric_limits<T>::max();

    void eval(int k){//ノードkの値を更新して遅延配列を伝播
        if(Lazy[k]){
            dat[k] += Lazy[k];
            if(k < n - 1) {
                Lazy[2 * k + 1] += Lazy[k];
                Lazy[2 * k + 2] += Lazy[k];
            }
            Lazy[k] = 0;
        }
    }

public:
    LazySegmentTree(const vector<T> &v) : sz((int)v.size()) {
        //nは元配列の要素数以上で最小の二冪
        //datは[n-1, 2n-1]が元の配列に対応　最下段より上段の要素数がn-1
        n = 1;
        while(n < sz)n *= 2;
        dat.resize(2 * n - 1, INF);//ノードを単位元で初期化
        Lazy.resize(2 * n - 1, 0);//遅延配列を0で初期化

        for(int i = 0; i < sz; i++){
            dat[i + n - 1] = v[i];//元配列に対応するノードを初期化
        }
        for(int i = n - 2; i >= 0; i--){
            dat[i] = min(dat[2 * i + 1], dat[2 * i + 2]);//下から上になめて更新
        }
    }

    //[a,b)にxを一様加算
    //今見てるノードのインデックス:k  それに対応する元配列の区間[l,r)

    void add(int a, int b, T x, int k = 0, int l = 0, int r = -1){
        if(r < 0)r = n;
        eval(k);
        if(r <= a && b <= l){//更新区間を含まない
            return;
        }
        if(l <= a && b <= r){//更新区間を完全に含む
            Lazy[k] += x;
            eval(k);
        }
        else {//一部更新区間を含む
            add(a, b, x, 2 * k + 1, l, (l + r) / 2);
            add(a, b, x, 2 * k + 2, (l + r) / 2, r);
        }
    }

    //[a,b)のminを求める
    T query(int a, int b, int k = 0, int l = 0, int r = -1){
        if(r < 0)r = n;
        if(r <= a && b <= l){
            return INF;//目的の区間を含まないので単位元を返す
        }

        eval(k);
        if(l <= a && b <= r){//遅延配列を更新してノードの値を返す
            return dat[k];
        }
        else {//左右に配って帰ってきた二つのminを返す
            T vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
            T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};

int main(){
    int N;
    cin >> N;
    vector<int> V(N);
    for(int i = 0; i < N; i++){
        cin >> V[i];
    }
    LazySegmentTree<int> seg(V);
    

    return 0;
}