#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

struct Tree {
    vector<int> tree, p;
    int size = 1;

    Tree(int n) {
        while (size < n) size <<= 1;
        tree.resize(2 * size - 1);
        p.resize(2 * size - 1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    struct node {
        int x, j;
    };
    vector<node> a;
    a.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;

        a.emplace_back(l - 1, i);
        a.emplace_back(r, i);
    }
    sort(a.begin(), a.end(), [&](node a, node b) {
        return a.x < b.x;
    });

    vector<vector<int>> m(n + 2);
    vector<vector<pair<int, int>>> s(n + 2);
    vector<int> cnt(n);
    int sum = 0, left = 0, _new = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (cnt[a[i].j] == 0) sum++, cnt[a[i].j] = 1;
        else sum--, left++, cnt[a[i].j] = 2;

        while (i + 1 < 2 * n && a[i].x == a[i + 1].x) {
            i++;
            if (cnt[a[i].j] == 0) sum++, cnt[a[i].j] = 1;
            else sum--, left++, cnt[a[i].j] = 2;
        }

        int d = min(left, n - left - sum);

        m[sum].push_back(_new);
        m[sum + 2 * d + 1].push_back(_new);

        s[sum + 2 * d].emplace_back(d, _new);
        s[sum + 2 * d + min(sum, n - 2 * d - sum) + 1].emplace_back(d, _new);

        _new++;
    }

    vector<int> c(_new), res(n + 1, 1e9);
    multiset<int> r;
    for (int i = 0; i <= n; ++i) {
        for (auto &j: m[i]) {
            if (c[j] == 0) r.insert(i), c[j] = i + 1;
            else r.extract(c[j] - 1);
        }
        if (r.empty()) continue;
        res[i] = (i - *r.rbegin() + 1) / 2;
    }

    multiset<pair<int, int>> r2;
    fill(c.begin(), c.end(), 0);
    for (int i = 0; i <= n; ++i) {
        for (auto &j: s[i]) {
            if (c[j.second] == 0) r2.emplace(j.first - i, j.second), c[j.second] = i + 1;
            else r2.extract({j.first - c[j.second] + 1, j.second});
        }
        if (r2.empty()) continue;
        res[i] = min(res[i], i + r2.rbegin()->first);
    }

    while (q--) {
        int k;
        cin >> k;

        cout << res[k] << " ";
    }
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
//    cin >> t;
    while (t--) solve();
}