#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;
using pii = pair<int,int>;
const int inf = 2e9;
const int M = 998244353;
const ld eps = 1e-9;
struct event {
    int x, type;// -1 close 1 open
    bool operator < (const event e){
        if (x != e.x) {
            return x < e.x;
        }
        return type < e.type;
    }
};

bool check(int cnt, vector<event> &e, int chm1, int chp2) {
    int ans = 0;
    int c = 0;
    for (int i = 1; i < e.size();i++) {
        if (chm1 < e[i].x && e[i-1].x == chm1) {
            e[i-1].type;
        }
    }
    for (auto [x, type] : e) {
        if (type == x) {

        }
    }
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    //freopen("input.txt","r",stdin);
    int n, q;
    cin >> n >> q;
    vector<pii> seg(n);
    for (int i =0;i < n;i++) {
        cin >> seg[i].first >> seg[i].second;
    }
    sort(seg.begin(), seg.end(), [](pii a, pii b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first > a.second;
    });
    while (q--) {
        int k;
        cin >> k;
        cout << 1 << " ";
    }
}