#include<bits/stdc++.h>
using namespace std;

template<typename T> class LazySegmentTree {
    int n, sz;
    vector<T> dat, Lazy;

    void eval(int k){
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
        dat.resize(2 * n - 1, numeric_limits<T>::max());
        Lazy.resize(2 * n - 1, 0);

        for(int i = 0; i < sz; i++){
            dat[i + n - 1] = v[i];
        }
        for(int i = n - 2; i >= 0; i--){
            dat[i] = min(dat[2 * i + 1], dat[2 * i + 2]);
        }
    }

    void update(int a, int b, T x, int k = 0, int l = 0, int r = -1){
        if(r < 0)r = n;
        if(r <= a && b <= l){
            return;
        }
        if(a <= l && r <= b){
            Lazy[k] += x;
            eval(k);
        }
        else {
            update(a, b, x, 2 * k + 1, l, (l + r) / 2);
            update(a, b, x, 2 * k + 2, (l + r) / 2, r);
        }
    }

    T query(int a, int b, int k = 0, int l = 0, int r = -1){
        if(r < 0)r = n;
        if(r <= a && b <= l){
            return numeric_limits<T>::max();
        }
        if(a <= l && r <= b){
            eval(k);
            return dat[k];
        }
        else {
            int vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
            int vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }
};

int main(){
    

    return 0;
}