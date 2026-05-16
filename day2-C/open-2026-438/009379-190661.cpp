#include <bits/stdc++.h>

using namespace std;

int sz = 1;

void apply(vector<int> &tree, vector<int> &add, int v, int x) {
    tree[v] += x;
    add[v] += x;
}

void push(vector<int> &tree, vector<int> &add, int v) {
    if (add[v] != 0) {
        apply(tree, add, 2 * v + 1, add[v]);
        apply(tree, add, 2 * v + 2, add[v]);
        add[v] = 0;
    }
}

void upd(vector<int> &tree, vector<int> &add, int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        apply(tree, add, v, x);
        return;
    }
    push(tree, add, v);
    int m = (l + r) / 2;
    upd(tree, add, 2 * v + 1, l, m, ql, qr, x);
    upd(tree, add, 2 * v + 2, m, r, ql, qr, x);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}

int get(vector<int> &tree, vector<int> &add, int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return tree[v];
    push(tree, add, v);
    int m = (l + r) / 2;
    return max(get(tree, add, 2 * v + 1, l, m, ql, qr), get(tree, add, 2 * v + 2, m, r, ql, qr));
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> mass(n);
    set<int> cords;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        mass[i] = {l, r};
        cords.insert(l);
        cords.insert(r);
    }
    map<int, int> mp;
    for (auto x : cords) {
        mp[x] = sz;
        sz++;
    }
    vector<int> tree(4 * sz, 0), add(4 * sz, 0);
    set<pair<int, int>> fst, snd;
    for (int i = 0; i < (int)mass.size(); i++) {
        auto &[l, r] = mass[i];
        l = mp[l];
        r = mp[r];
        fst.insert({l, i});
        snd.insert({r, i});
        upd(tree, add, 0, 0, sz, l, r + 1, 1);
    }
    vector<pair<int, int>> qs(q);
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        qs[i] = {k, i};
    }
    vector<int> ans(q);
    sort(qs.begin(), qs.end());
    int idx = 0;
    int cnt = 0;
    while (idx < q) {
        int res = get(tree, add, 0, 0, sz, 0, sz);
        while (idx < q && res >= qs[idx].first) {
            ans[qs[idx].second] = cnt;
            idx++;
        }
        cnt++;
        auto [a, i1] = *(--fst.end());
        fst.erase({a, i1});
        snd.erase({mass[i1].second, i1});
        auto [b, i2] = *snd.begin();
        snd.erase({b, i2});
        fst.erase({mass[i2].first, i2});
        upd(tree, add, 0, 0, sz, mass[i1].first, mass[i1].second + 1, -1);
        upd(tree, add, 0, 0, sz, mass[i2].first, mass[i2].second + 1, -1);
        mass[i1].first = mass[i2].first;
        mass[i2].first = mass[i2].second;
        mass[i2].second = a;
        upd(tree, add, 0, 0, sz, mass[i1].first, mass[i1].second + 1, 1);
        upd(tree, add, 0, 0, sz, mass[i2].first, mass[i2].second + 1, 1);
        snd.insert({mass[i2].second, i2});
        fst.insert({mass[i2].first, i2});
    }
    for (auto x : ans) cout << x << " ";
    cout << endl;
    return 0;
}
