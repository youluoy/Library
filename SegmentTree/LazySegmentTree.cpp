#include<bits/stdc++.h>
using namespace std;

template<typename T> class LazySegmentTree {
    int n, sz;
    vector<T> dat, Lazy;
    const T INF = (1 << 30) - 1;

    void eval(int k){//ノードkの値を更新して遅延配列を伝播
        dat[k] += Lazy[k];//ココ
        if(Lazy[k]){
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
    //ノードの値を更新

    void add(int a, int b, T x, int k = 0, int l = 0, int r = -1){
        if(r < 0)r = n;
        eval(k);//ココ
        if(r <= a || b <= l){//更新区間にふくまれない
            return;
        }
        if(a <= l && r <= b){//更新区間に完全に含まれる
            Lazy[k] += x;
            eval(k);
        }
        else {//一部更新区間を含む
            add(a, b, x, 2 * k + 1, l, (l + r) / 2);
            add(a, b, x, 2 * k + 2, (l + r) / 2, r);
            if(k < n - 1){//ココ
                dat[k] = min(dat[2 * k + 1], dat[2 * k + 2]);
            }
        }
        
    }

    //[a,b)のminを求める
    T query(int a, int b, int k = 0, int l = 0, int r = -1){
        if(r < 0)r = n;
        if(r <= a || b <= l){
            return INF;//目的の区間を含まないので単位元を返す
        }

        eval(k);
        if(a <= l && r <= b){//遅延配列を更新してノードの値を返す
            return dat[k];
        }
        else {//左右に配って帰ってきた二つのminを返す
            T vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
            T vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};
