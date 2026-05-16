//#define _GLIBCXX_DEBUG
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

//#define int long long

using namespace std;
using ll = long long;
using ld = long double;

const int INFI = 2e9 + 5, MAXN = 1e5 + 1, MOD = 998244353;
const ll INF = 9e18 + 5;

struct Segtree {
    vector<int> tree, lazy;
    int sz;

    void init(int n) {
        sz = n;
        tree.resize(n * 4, INFI);
        lazy.resize(n * 4, 0);
    }

    void push(int x, int lx, int rx) {
        if (!lazy[x])
            return;
        tree[x] += lazy[x];
        if (lx + 1 != rx) {
            lazy[x * 2 + 1] += lazy[x];
            lazy[x * 2 + 2] += lazy[x];
        }
        lazy[x] = 0;
    }

    void update1(int x, int lx, int rx, int i, int v) {
        push(x, lx, rx);
        if (lx > i || rx <= i)
            return;
        if (lx + 1 == rx) {
            tree[x] = min(tree[x], v);
            if (v == INFI)
                tree[x] = v;
            return;
        }
        int mid = (lx + rx) / 2;
        update1(x * 2 + 1, lx, mid, i, v);
        update1(x * 2 + 2, mid, rx, i, v);
        tree[x] = min(tree[x * 2 + 1], tree[x * 2 + 2]);
    }

    void update2() {
        lazy[0]++;
    }

    int get() {
        push(0, 0, sz);
        return tree[0];
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> ans(n + 1, INFI);
    vector<pair<int, int> > v;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        v.push_back({l, 0});
        v.push_back({r, 1});
    }
    sort(v.begin(), v.end());
    vector<vector<pair<int, int> > > tempone(n + 5), temptwo(n + 5);
    int ch1 = n, ch2 = 0, chnow = 0;
    for (int i = 0; i < v.size(); ++i) {
        int fl = v[i].second;
        if (!fl) {
            ch1--;
            chnow++;
        } else {
            ans[chnow] = 0;
            int free = chnow;
            int two = min(ch1, ch2);
            int one = max(ch1, ch2) - min(ch1, ch2);
            chnow--;
            ch2++;
            tempone[free + 2 * two + 1].push_back({free + 2 * two + one + 1, two + 1});
            temptwo[free + 1].push_back({free + 2 * two + 1, 1});
        }
    }
    for (int i = n - 1; i > -1; --i) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    Segtree stone;
    stone.init(n + 2);
    for (int i = 1; i <= n; ++i) {
        stone.update1(0, 0, n + 2, i, INFI);
        stone.update2();
        for (auto& nd : tempone[i]) {
            //cout << i << ' ' << nd.first << ' ' << nd.second << "!\n";
            stone.update1(0, 0, n + 2, nd.first, nd.second);
        }
        ans[i] = min(ans[i], stone.get());
    }
    Segtree sttwo1, sttwo2;
    sttwo1.init(n + 2);
    sttwo2.init(n + 2);
    for (int i = 1; i <= n; i += 2) {
        sttwo1.update1(0, 0, n + 2, i, INFI);
        sttwo1.update2();
        for (auto& nd : temptwo[i]) {
            //cout << i << ' ' << nd.first << ' ' << nd.second << "@\n";
            if (nd.first != i)
                sttwo1.update1(0, 0, n + 2, nd.first, nd.second);
        }
        ans[i] = min(ans[i], sttwo1.get());
        ans[i + 1] = min(ans[i + 1], sttwo1.get());
    }
    for (int i = 2; i <= n; i += 2) {
        sttwo2.update1(0, 0, n + 2, i, INFI);
        sttwo2.update2();
        for (auto& nd : temptwo[i]) {
            if (nd.first != i)
                sttwo2.update1(0, 0, n + 2, nd.first, nd.second);
        }
        ans[i] = min(ans[i], sttwo2.get());
        ans[i + 1] = min(ans[i + 1], sttwo2.get());
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while (t--)
        solve();
    return 0;
}
