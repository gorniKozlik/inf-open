#include <bits/stdc++.h>
using namespace std;
#define int long long
#ifndef LOCAL
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2")
#endif
struct segtree {
    vector<pair<int, int>> tree;
    segtree(int n) { tree.resize(2 * n); }

    int get(int x, int l, int r, int f) {
        int m = (r + l) / 2;
        int lv = x + 1, rv = x + 2 * (m - l);
        if (r - l == 1) {
            return l;
        }
        if (f == -1) {
            if (tree[lv].first != 0) {
                return get(lv, l, m, f);
            } else {
                return get(rv, m, r, f);
            }
        } else {
            if (tree[rv].second != 0) {
                return get(rv, m, r, f);
            } else {
                return get(lv, l, m, f);
            }
        }
    }
    void upd(int x, int l, int r, int f, int pos) {
        if (r - l == 1) {
            if (f == -1) {
                tree[x] = {1, 0};
            } else {
                tree[x] = {0, 1};
            }
            return;
        }
        int m = (r + l) / 2;
        int lv = x + 1, rv = x + 2 * (m - l);
        if (pos < m) {
            upd(lv, l, m, f, pos);
        } else {
            upd(rv, m, r, f, pos);
        }
        tree[x].first = tree[lv].first + tree[rv].first;
        tree[x].second = tree[lv].second + tree[rv].second;
    }
};
struct stree {
    struct node {
        int push = 0, mn = 0;
    };
    vector<node> tree;
    stree(int n) { tree.resize(2 * n); }
    void push(int x, int l, int r) {
        if (r - l == 1 || tree[x].push == 0)
            return;
        int m = (r + l) / 2;
        int lv = x + 1, rv = x + 2 * (m - l);
        tree[lv].mn += tree[x].push;
        tree[rv].mn += tree[x].push;
        tree[lv].push += tree[x].push;
        tree[rv].push += tree[x].push;
        tree[x].push = 0;
    }
    int get(int x, int l, int r, int ql, int qr) {
        push(x, l, r);
        if (ql >= r || l >= qr)
            return -1e16;
        if (ql <= l && qr >= r)
            return tree[x].mn;
        int m = (r + l) / 2;
        int lv = x + 1, rv = x + 2 * (m - l);
        return max(get(lv, l, m, ql, qr), get(rv, m, r, ql, qr));
    }
    void upd(int x, int l, int r, int ql, int qr, int val) {
        push(x, l, r);
        if (ql >= r || l >= qr)
            return;
        if (ql <= l && qr >= r) {
            tree[x].mn += val;
            tree[x].push += val;
            return;
        }
        int m = (r + l) / 2;
        int lv = x + 1, rv = x + 2 * (m - l);
        upd(lv, l, m, ql, qr, val);
        upd(rv, m, r, ql, qr, val);
        tree[x].mn = max(tree[lv].mn, tree[rv].mn);
    }
};
signed main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
#ifdef LOCAL
    freopen("./../input.txt", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        a.push_back({l, i + 1});
        a.push_back({r, -i - 1});
    }
    n *= 2;
    sort(a.begin(), a.end());
    segtree fnd(n);
    stree tree(n);
    vector<int> ans(n + 1);
    vector<int> pr(n);
    int cnt = 0;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        if (a[i].second > 0) {
            cnt++;
            mp[a[i].second - 1] = i;
            fnd.upd(0, 0, n, 1, i);
        }

        tree.upd(0, 0, n, i, i + 1, cnt);
        if (a[i].second < 0) {
            cnt--;
            fnd.upd(0, 0, n, -1, i);

            pr[i] = mp[-a[i].second - 1];
            pr[mp[-a[i].second - 1]] = i;
        }
    }
    // for (int i = 0; i < n; i++) {
    //     cout << tree.get(0, 0, n, i, i + 1) << " ";
    // }
    // cout << endl;
    for (int i = 0; i <= n; i++) {
        ans[i] = tree.get(0, 0, n, 0, n);
        int ql = fnd.get(0, 0, n, -1);
        int qr = fnd.get(0, 0, n, 1);
        int qql = pr[ql];
        int qqr = pr[qr];
        if (ql > qr)
            break;
        tree.upd(0, 0, n, ql + 1, qr, 2);
        tree.upd(0, 0, n, ql, ql + 1, 1);
        tree.upd(0, 0, n, qr, qr + 1, 1);

        fnd.upd(0, 0, n, 1, ql);
        fnd.upd(0, 0, n, -1, qr);
    }
    for (int i = 0; i < n; i++) {
        ans[i + 1] = max(ans[i], ans[i + 1]);
    }
    vector<int> qwe(n + 1);
    while (q--) {
        int k;
        cin >> k;
        cout << lower_bound(ans.begin(), ans.end(), k) - ans.begin() << " ";
    }
    cout << endl;
    return 0;
}