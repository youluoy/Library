#include<bits/stdc++.h>
using namespace std;

int select_pivot(vector<int> &v){
    int vsz = (int)v.size();
    int vsz5 = (vsz + 4) / 5;

    ///split v
    vector<vector<int> > v1(vsz5, vector<int>(5));
    for(int i = 0; i < vsz; i++){
        v1[i / 5][i % 5] = v[i];
    }

    ///sort to each v splited
    vector<int> v2(vsz5);
    for(int i = 0; i < vsz5; i++){
        auto end = (i == vsz5 - 1) ? (v1[i].begin() + vsz % 5) : v1[i].end();
        sort(v1[i].begin(), end);
        v2[i] = v1[i][(end - v1[i].begin()) / 2];
    }

    ///return pivot
    if(vsz5 <= 5){
        sort(v2.begin(), v2.end());
        return v2[(int)v2.size() / 2];
    }
    else {
        return select_pivot(v2);
    }
}

int select_median(vector<int>& v, int k, int l = 0, int r = -1){
    int vsz = (int)v.size();
    if(r == -1)r = vsz - 1;

    vector<int> pv(r - l + 1);
    for(int i = l, j = 0; i <= r; i++, j++){
        pv[j] = v[i];
    }
    int pivot = select_pivot(pv);

    ///v[l:r] to [less than pivot, equal to pivot, greater than pivot]
    
    ///v[l:r] to [less than pivot, greater than or equal to pivot]
    int left, right;
    for(left = l, right = r; left < right;){
        while(v[left] < pivot)left++;
        while(v[right] >= pivot)right--;
        if(left < right)swap(v[left], v[right]);
    }

    ///v[left:r] to [equal to pivot, greater than pivot]
    int left2, right2;
    for(left2 = left, right2 = r; left2 < right2;){
        while(v[left2] == pivot)left2++;
        while(v[right2] > pivot)right2--;
        if(left2 < right2)swap(v[left2], v[right2]);
    }

    if(left <= k && k <= right2){
        return v[k];
    }
    else {
        if(k < left){
            return select_median(v, k, l, right);
        }
        else {
            return select_median(v, k, left2, r);
        }
    }

}