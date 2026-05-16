//#define _GLIBCXX_DEBUG
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

vector<pii> seg;


bool cmp(int a, int b) {
    return seg[a].f < seg[b].f;
}

bool cmp1(int a, int b) {
    return seg[a].s > seg[b].s;
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    set<pii> c;
    vector<int> ans(n + 1, -1);
    vector<int> left, right;
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
    for (int i = 0; i < n; ++i) {
        auto [l, r] = seg[i];
        if (mp[r] < n) left.push_back(i);
        if (mp[l] >= n) right.push_back(i);
    }
    sort(left.begin(), left.end(), cmp);
    sort(right.begin(), right.end(), cmp1);
    int sz = 2 * n;
    t.resize(4 * sz);
    add.resize(4 * sz);
    for (auto [l, r] : seg) {
        upd(0, 0, sz, mp[l], mp[r] + 1, 1);
    }
    int res = 0;
    int mx = t[0];
    ans[mx] = 0;
    for (int i = 0; i < left.size(); ++i) {
        res++;
        int l1 = mp[seg[left[i]].f];
        int r1 = mp[seg[left[i]].s];
        int l2 = mp[seg[right[i]].f];
        int r2 = mp[seg[right[i]].s];
        upd(0, 0, sz, l1, r1 + 1, -1);
        upd(0, 0, sz, l2, r2 + 1, -1);
        upd(0, 0, sz, l1, r2 + 1, 1);
        upd(0, 0, sz, r1, l2 + 1, 1);
        mx = t[0];
        if (ans[mx] == -1) ans[mx] = res;

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

