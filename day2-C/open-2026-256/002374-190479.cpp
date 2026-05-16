#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
//#pragma GCC optimize("O3,Ofast,unroll-loops")
#pragma GCC target("avx2")

using namespace __gnu_pbds;
using namespace std;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Node {
    int p;
    int a;
};

vector<Node> t;

void push(int v) {
    if (t[v].p != 0) {
        int x = t[v].p;
        t[2 * v].a += x;
        t[2 * v].p += x;
        t[2 * v +1].a += x;
        t[2 * v + 1].p += x;
        t[v].p = 0;
    }
}

void pl(int v, int ql, int qr, int vl, int vr, int x) {
    if (qr <= vl || vr <= ql) return;
    if (vl <= ql && qr <= vr) {
        t[v].a += x;
        t[v].p += x;
        return;
    }
    push(v);
    pl(2 * v, ql, (ql + qr) / 2, vl, vr, x);
    pl(2 * v + 1, (ql + qr) / 2, qr, vl, vr, x);
    t[v].a = max(t[2 * v].a, t[2 * v + 1].a);
}

int cl_[200000];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    set<int> s;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        s.insert(a[i].first);
        s.insert(a[i].second);
    }
    int cr = 1;
    unordered_map<int, int> mp;
    vector<int> l_w;
    for (auto x : s) {
        l_w.push_back(x);
    }
    for (auto x : l_w) {
        mp[x] = cr++;
    }
    set<pair<int, int>> left, right;
    for (int i = 0; i < n; ++i) {
        a[i].first = mp[a[i].first];
        a[i].second = mp[a[i].second];
        left.insert({-a[i].first, a[i].second});
        right.insert({a[i].second, a[i].first});
    }
    int n1 = 1;
    while (n1 < cr) n1 *= 2;
    t.resize(2 * n1);
    for (auto x : a) {
        pl(1, 0, n1, x.first, x.second, 1);
    }
    int sm = 0;
    int nw = 0;
    for (int j = 0; j <= n; ++j) {
        int now = t[1].a;
        for (int i = nw; i <= now; ++i) {
            cl_[i] =sm;
        }
        nw = now + 1;
        pair<int, int> r_ = *right.begin(), l_ = *left.begin();
        swap(r_.first, r_.second);
        l_.first *= -1;
        sm++;
        if (r_.second > l_.first) break;
        pl(1, 0, n1,r_.second, l_.first, 2);
        right.erase(right.begin());
        right.erase(right.find({l_.second, l_.first}));

        left.erase(left.find({-r_.first, r_.second}));
        left.erase(left.begin());

        swap(r_.second, l_.first);
        right.insert({r_.second, r_.first});
        right.insert({l_.second, l_.first});
        left.insert({-l_.first, l_.second});
        left.insert({-r_.first, r_.second});
    }
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        cout << cl_[x] << '\n';
    }
}