#include <iostream>
#include <bits/stdc++.h>
#include <random>
using namespace std;

long long inf = 1e17;

// random_device rd;
// mt19937 rnd(rd);
// uniform_int_distribution<> gen(0, 5);

struct Tree {
    vector<int> tree;
    void add(int x, int l, int r, int id) {
        if (r - l == 1) {
            tree[x]++;
            return;
        }
        int m = (r + l) / 2;
        if (id < m) {
            add(2 * x + 1, l, m, id);
        } else {
            add(2 * x + 2, m, r, id);
        }
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    int get(int x, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[x];
        }
        int m = (r + l) / 2;
        return get(2 * x + 1, l, m, ql, qr) + get(2 * x + 2, m, r, ql, qr);
    }
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    Tree tree;
    tree.tree.resize(8 * n);
    vector<int> res(n + 1, n + 1);
    vector<pair<int, int>> p(n);
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i] = {x, y};
        v.push_back(x);
        v.push_back(y);
    }
    sort(v.begin(), v.end());
    for (auto& [x, y] : p) {
        x = lower_bound(v.begin(), v.end(), x) - v.begin();
        y = lower_bound(v.begin(), v.end(), y) - v.begin();
    }

    sort(p.begin(), p.end());
    int id = 0;
    for (int i = 0; i < n * 2; i++) {
        while (id < n && p[id].first <= i) {
            auto [x, y] = p[id];
            tree.add(0, 0, 2 * n, y);
            id++;
        }
        int cnt = tree.get(0, 0, 2 * n, i, 2 * n);
        for (int k = 0; k <= min(cnt, 10); k++) {
            res[k] = 0;
        }
        int l = id - cnt;
        int r = n - cnt - l;
        int ans = 0;
        while (l > 0 && r > 0 && cnt < 10) {
            res[cnt + 1] = min(res[cnt + 1], ans + 1);
            res[cnt + 2] = min(res[cnt + 2], ans + 1);
            ans++;
            cnt += 2;
            r--;
            l--;
        }
        while ((l > 0 || r > 0) && cnt < 10) {
            res[cnt + 1] = min(res[cnt + 1], ans + 1);
            ans++;
            cnt++;
            r--;
            l--;
        }
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << res[k] << '\n';
    }
}