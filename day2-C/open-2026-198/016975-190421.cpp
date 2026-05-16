#include<bits/stdc++.h>

// #define int long long
// #pragma GCC optimize("O3, unroll-loops")
// #pragma GCC target("avx2")

using ll = long long;
using namespace std;

struct Node {
    int val = 0, left = -1, right = -1, mod = 0;
};

vector<Node> t;

void push(int v) {
    if (t[v].mod == 0) {
        return;
    }
    t[t[v].left].mod += t[v].mod;
    t[t[v].right].mod += t[v].mod;
    t[t[v].left].val += t[v].mod;
    t[t[v].right].val += t[v].mod;
    t[v].mod = 0;
}

void update(int v, int l, int r, int ql, int qr, int new_val) {
    if (ql == qr) {
        return;
    }
    if (l >= qr || ql >= r) {
        return;
    }
    if (ql <= l && r <= qr) {
        t[v].val += new_val;
        t[v].mod += new_val;
        return;
    }
    int m = (r + l) / 2;
    if (t[v].left == -1 && t[v].right == -1) {
        t[v].left = t.size();
        t.push_back(Node());
        t[v].right = t.size();
        t.push_back(Node());
    }
    push(v);
    update(t[v].left, l, m, ql, qr, new_val);
    update(t[v].right, m, r, ql, qr, new_val);
    t[v].val = max(t[t[v].left].val, t[t[v].right].val);
}

// int get(int v, int l, int r, int ind) {
//     if (l + 1 == r) {
//         return t[v].val;
//     }
//     int m = (r + l) / 2;
//     if (ind < m) {
//         if (t[v].left == -1) {
//             return t[v].val;
//         }
//         return get(t[v].left, l, m, ind);
//     } else {
//         if (t[v].right == -1) {
//             return t[v].val;
//         }
//         return get(t[v].right, m, r, ind);
//     }
// }

// void print(int mx) {
//     for (int i = 1; i <= mx; i++) {
//         cout << get(0, 0, mx + 1, i) << " ";
//     }
//     cout << "\n";
// }

void solve() {
    int n, q, mx = 0, cnt = 0, prev = 0;
    cin >> n >> q;
    set<pair<int, int>> st1, st2;
    vector<pair<int, int>> a;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        st1.insert({r, l});
        st2.insert({-l, r});
        a.push_back({l, -1});
        a.push_back({r + 1, 1});
        mx = max(mx, r);
    }
    t.push_back(Node());
    sort(a.begin(), a.end());
    for (int i = 0; i < (int)a.size(); i++) {
        if (i == (int)a.size() - 1 || a[i].first != a[i + 1].first) {
            update(0, 0, mx + 1, prev, a[i].first, cnt);
        }
        prev = a[i].first;
        cnt -= a[i].second;
    }
    // print(mx);
    // update(0, 0, mx + 1, prev, mx + 1, cnt);
    // print(mx);
    ans.push_back(t[0].val);
    while (true) {
        auto [r1, l1] = *st1.begin();
        auto [l2, r2] = *st2.begin();
        // cout << l1 << " " << r1 << " " << l2 << " " << r2 << "\n";
        l2 = -l2;
        if (l2 <= r1) {
            break;
        }
        st1.erase(st1.begin());
        st1.erase(st1.find({r2, l2}));
        st2.erase(st2.begin());
        st2.erase(st2.find({-l1, r1}));
        update(0, 0, mx + 1, r1, r1 + 1, 1);
        update(0, 0, mx + 1, r1 + 1, l2, 2);
        update(0, 0, mx + 1, l2, l2 + 1, 1);
        // print(mx);
        ans.push_back(t[0].val);
        st1.insert({r2, l1});
        st1.insert({l2, r1});
        st2.insert({-l1, r2});
        st2.insert({-r1, l2});
    }
    while (q--) {
        int k;
        cin >> k;
        int l = -1, r = ans.size();
        while (r - l > 1) {
            int m = (r + l) / 2;
            if (ans[m] >= k) {
                r = m;
            } else {
                l = m;
            }
        }
        cout << r << " ";
    }
    cout << "\n";
}

signed main() {
    int tests = 1;
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // cin >> tests;
#else
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
    // cin >> tests;
    while (tests--) {
        solve();
    }
}
