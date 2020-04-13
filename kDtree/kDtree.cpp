#include<bits/stdc++.h>
using namespace std;
#define INF (1ll << 30ll)


struct point{
    int id, x, y;
    point(){
        id = -1, x = 0, y = 0;
    }
    point(int a, int b, int c){
        id = a, x = b, y = c;
    }
    point& operator = (const point &a){
        id = a.id, x = a.x, y = a.y;
        return *this;
    }
};

bool cmp_id(const point& a, const point& b){
    return a.id < b.id;
}

void PrintVector(const vector<point>& v, int is_x = 1, int is_endl = 1){
    for(int i = 0; i < (int)v.size(); i++){
        if(is_x == 1)cout << v[i].x << " ";
        else if(is_x == 0) cout << v[i].y << " ";
        else cout << v[i].x << "," << v[i].y << "\\";
    }
    if(is_endl)cout << endl;
}

struct Node{
    vector<point> pointlist;
    int xmax, ymax, xmin, ymin;
    Node *left, *right, *par;

    Node(){
        xmax = ymax = -INF;
        xmin = ymin = INF;
        left = right = par = NULL;
    }

    Node(vector<point>& v, int l = 0, int r = -1){
        if(r == -1)r = v.size();

        pointlist.resize(r - l);
        xmax = ymax = -INF;
        xmin = ymin = INF;
        for(int i = l; i < r; i++){
            pointlist[i - l] = v[i];
            xmax = max(xmax, pointlist[i - l].x);
            ymax = max(ymax, pointlist[i - l].y);
            xmin = min(xmin, pointlist[i - l].x);
            ymin = min(ymin, pointlist[i - l].y);
        }
        left = right = par = NULL;
    }

};

struct kDtree{
    Node* root;

    kDtree(){
        root = NULL;
    }
    
    kDtree(vector<point>& v, int k = 0, int l = 0, int r = -1){
        root = BuildTree(v, k, l, r);

    }
    
    ~kDtree(){
        delete root;
    }

    Node* BuildTree(vector<point>& v, int k = 0, int l = 0, int r = -1){
        if(r == -1)r = v.size();

        //make mynode
        Node* mynode = new Node(v, l, r);

        if(r - l == 1)return mynode;

        ///find median
        point median = select_median(mynode->pointlist, (r - l) / 2, k);//TODO select_median imprement ok

        int lid = 0, rid = (int)mynode->pointlist.size() - 1;

        ///this v change to [中央値未満, 中央値以上]
        while(lid < rid){
            while(cmp_points(median, mynode->pointlist[lid], k)){//TODO cmp_points imprement ok
                lid++;
                if(lid > rid)break;
            }
            while(!cmp_points(median, mynode->pointlist[rid], k)){
                rid--;
                if(lid > rid)break;
            }
            if(lid < rid)swap(mynode->pointlist[lid], mynode->pointlist[rid]);
        }

        
        ///make children
        k++;
        k %= 2;
        mynode->left = BuildTree(mynode->pointlist, k, 0, lid);
        mynode->right = BuildTree(mynode->pointlist, k, lid);

        return mynode;
    }

    bool cmp_points(const point& a, const point& b, int k){
        if(k == 0){
            return a.x > b.x || (a.x == b.x && a.y > b.y);
        }
        else {
            return a.y > b.y || (a.y == b.y && a.x > b.x);
        }
    }

    void sort_pointlist(vector<point>& v, int k, int sz = -1){
        if(sz == -1)sz = (int)v.size();
        for(int i = 0; i < sz; i++){
            point minp = v[i];
            int minid = i;
            for(int j = i + 1; j < sz; j++){
                if(cmp_points(minp, v[j], k)){
                    minp = v[j];
                    minid = j;
                }
            }
            swap(v[i], v[minid]);
        }
    }

    point select_pivot(vector<point> &v, int k){//TODO add int k
        int vsz = (int)v.size();
        int vsz5 = (vsz + 4) / 5;

        ///split v
        vector<vector<point> > v1(vsz5, vector<point>(5));
        for(int i = 0; i < vsz; i++){
            v1[i / 5][i % 5] = v[i];
        }

        ///sort to each v splited
        vector<point> v2(vsz5);
        for(int i = 0; i < vsz5; i++){
            int endid = (i == vsz5 - 1) ? vsz % 5 : 5;
            sort_pointlist(v1[i], k, endid);///sort TODO
            v2[i] = v1[i][endid / 2];
        }

        ///return pivot
        if(vsz5 <= 5){
            sort_pointlist(v2, k);///sort TODO
            return v2[(int)v2.size() / 2];
        }
        else {
            return select_pivot(v2, k);
        }
    }

    point select_median(vector<point>& v, int retk, int k, int l = 0, int r = -1){
        int vsz = (int)v.size();
        if(r == -1)r = vsz - 1;

        vector<point> pv(r - l + 1);
        for(int i = l; i <= r; i++){
            pv[i - l] = v[i];
        }
        point pivot = select_pivot(pv, k);

        ///v[l:r] to [less than pivot, equal to pivot, greater than pivot]
        
        ///v[l:r] to [less than pivot, greater than or equal to pivot]
        int left, right;
        for(left = l, right = r; left < right;){
            while(cmp_points(pivot, v[left], k)){
                left++;
                if(left > right)break;
            }
            while(!cmp_points(pivot, v[right], k)){
                right--;
                if(left > right)break;
            }
            if(left < right)swap(v[left], v[right]);
        }

        ///v[left:r] to [equal to pivot, greater than pivot]
        int left2, right2;
        for(left2 = left, right2 = r; left2 < right2;){
            while(pivot.x == v[left2].x && pivot.y == v[left2].y){
                left2++;
                if(left2 > right2)break;
            }
            while(cmp_points(v[right2], pivot, k)){
                right2--;
                if(left2 > right2)break;
            }
            if(left2 < right2)swap(v[left2], v[right2]);
        }

        if(left <= retk && retk <= right2){
            return v[retk];
        }
        else {
            if(retk < left){
                return select_median(v, retk, k, l, right);
            }
            else {
                return select_median(v, retk, k, left2, r);
            }
        }
    }

    void PrintkDtree(){
        queue<void*> que;
        que.push(root);
        int cnt = 0, bmod = 0;
        while(!que.empty()){
            Node* cur = (Node*)que.front();
            que.pop();
            
            PrintVector(cur->pointlist, 2, 0);

            if(bmod > 0){
                cnt++;
                if(cnt % bmod == 0){
                    cout << endl;
                    bmod *= 2;
                    cnt = 0;
                }
                else {
                    cout << " \\";
                }
            }
            else {
                cout << endl;
                bmod = 2;
            }

            if(cur->left != NULL)que.push(cur->left);
            if(cur->right != NULL)que.push(cur->right);
            
        }
    }

    void ReportSubTree(vector<point>& v, Node* var){
        for(int i = 0; i < (int)var->pointlist.size(); i++){
            v.emplace_back(var->pointlist[i]);
        }
    }

    void RangeSearch(vector<point>& v, int sx, int sy, int tx, int ty, Node* var = NULL){
        if(var == NULL)var = root;

        if(sx <= var->xmin && var->xmax <= tx && sy <= var->ymin && var->ymax <= ty){
            ReportSubTree(v, var);
        }
        else if(sx > var->xmax || sy > var->ymax || tx < var->xmin || ty < var->ymin){
            return;
        }
        else {
            if(var->left != NULL)RangeSearch(v, sx, sy, tx, ty, var->left);
            if(var->right != NULL)RangeSearch(v, sx, sy, tx, ty, var->right);
        }
    }

};
