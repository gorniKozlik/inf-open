#define _GLIBCXX_DEBUG
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

#define f first
#define s second
#define pii pair<int, int>

vector<int> t, add;

void push(int v) {
    t[2 * v + 1] += add[v];
    t[2 * v + 2] += add[v];
    add[2 * v + 1] += add[v];
    add[2 * v + 2] += add[v];
    add[v] = 0;
}

void upd(int v, int l, int r, int ql, int qr, int x) {
    if (ql <= l && r <= qr) {
        t[v] += x;
        add[v] += x;
        return;
    }
    if (qr <= l || r <= ql) return;
    push(v);
    int m = (l + r) / 2;
    upd(2 * v + 1, l, m, ql, qr, x);
    upd(2 * v + 2, m, r, ql, qr, x);
    t[v] = max(t[2 * v + 1], t[2 * v + 2]);
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<pii> seg;
    set<pii> c;
    vector<int> ans(n + 1, -1);
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        seg.push_back({l, r});
        c.insert({l, i});
        c.insert({r, i});
    }
    unordered_map<int, int> mp, rmp;
    int cnt = 0;
    vector<int> col(2 * n);
    for (auto [el, i] : c) {
        mp[el] = cnt;
        rmp[cnt] = el;
        col[cnt] = i;
        ++cnt;
    }
    int sz = 2 * n;
    t.resize(4 * sz);
    add.resize(4 * sz);
    for (auto [l, r] : seg) {
        upd(0, 0, sz, mp[l], mp[r] + 1, 1);
    }
//    int mx = t[0];
//    for (int i = 1; i <= mx; ++i) {
//        ans[i] = 0;
//    }
    int i = 0, j = 2 * n - 1;
    int res = 0;
    while (i <= j) {
        int mx = t[0];
        //cout << mx << endl;
        if (ans[mx] == -1) ans[mx] = res;

        if (col[i] == col[j]) {
            ++i;
            --j;
            continue;
        }
        //cout << i << " " << j << endl;
        int n1 = col[i];
        int n2 = col[j];
        auto [l1, r1] = seg[n1];
        auto [l2, r2] = seg[n2];
        //exit(0);
        upd(0, 0, sz, mp[l1], mp[r1] + 1, -1);
        upd(0, 0, sz, mp[l2], mp[r2] + 1, -1);
        vector<int> cord;
        cord.push_back(mp[l1]);
        cord.push_back(mp[l2]);
        cord.push_back(mp[r1]);
        cord.push_back(mp[r2]);
        sort(cord.begin(), cord.end());
        col[cord[0]] = col[cord[3]] = n1;
        col[cord[1]] = col[cord[2]] = n2;
        upd(0, 0, sz, cord[0], cord[3] + 1, 1);
        upd(0, 0, sz, cord[1], cord[2] + 1, 1);
        ++res;
        ++i;
        --j;
        //exit(0);
    }
    for (int i = n - 1; i > 0; --i) {
        if (ans[i] == -1) {
            ans[i] = ans[i + 1];
        }
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
}

