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
        return type > e.type;
    }
};

int check(vector<event> &e) {
    int ans = 0;
    int c = 0;
    for (auto [x, type] : e) {
        if (type == 1) {
            c++;
        }else {
            ans = max(ans, c);
            c--;
        }
    }
    return ans;
}
vector<int> ans;
void solve(vector<pii> &seg) {
    int cnt = 0;
    int ll = 0, rr = seg.size()-1;
    vector<event> e;
    ans[0] = 0;
    int n = seg.size();
    e.reserve(2*n+1);
    for (auto [l, r] : seg) {
        e.push_back({l, 1});
        e.push_back({r, -1});
    }

    sort(e.begin(), e.end());
    auto z = check(e);
    ans[z] = cnt;
    while (ll < rr) {
        auto z0 = seg[ll];
        auto z1 = seg[rr];
        seg[ll] = {min(z0.second,z1.first),max(z0.second,z1.first)};
        seg[rr] = {min(z0.first, z1.second), max(z0.first, z1.second)};
        cnt++;
        vector<event> ee;

        for (auto [l, r] : seg) {
            ee.push_back({l, 1});
            ee.push_back({r, -1});
        }

        sort(ee.begin(),ee.end());
        auto f = check(ee);
        ans[f] = min(ans[f], cnt);
        ll++;
        rr--;
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
    ans.resize(n+1, inf);
    sort(seg.begin(), seg.end(), [](pii a, pii b) {
        if (a.second != b.second) {
            return a.second < b.second;
        }
        return a.first < a.second;
    });
    solve(seg);
    int last = ans[n];
    for (int i = n-1;i>=0;i--) {
        if (ans[i] == inf) {
            ans[i] = last;
        }else {
            last = min(last,ans[i]);
            ans[i] = last;
        }
    }
    while (q--) {
        int k; cin >> k;
        cout << ans[k] << " ";
    }
}