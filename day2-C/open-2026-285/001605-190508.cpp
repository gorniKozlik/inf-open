#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define all(a) a.begin(), a.end()

int tree[800000];
int add[800000];


void push(int v) {
    tree[2 * v + 1] += add[v];
    tree[2 * v + 2] += add[v];
    add[2 * v + 1] += add[v];
    add[2 * v + 2] += add[v];
    add[v] = 0;
}

void upd(int v, int l, int r, int ql, int qr, int x) {
    if (ql >= r || l >= qr) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v] += x;
        add[v] += x;
        return;
    }
    push(v);
    int mid = (r + l)/2;
    upd(2 * v + 1, l, mid, ql, qr, x);
    upd(2 * v + 2, mid, r, ql, qr, x);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    return;
}

void bt(int v, int l, int r, vector<int>&a) {
    if (l + 1 == r) {
        tree[v] = a[l];
        return;
    }
    int mid = (r + l)/2;
    bt(2 * v + 1, l, mid, a);
    bt(2 * v + 2, mid, r, a);
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    return;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>>o(n);
    vector<int>x_compress;
    x_compress.reserve(2 * n);
    set<int>l;
    set<int>r;
    for (int i = 0; i < n; i++) {
        cin >> o[i].first >> o[i].second;
        x_compress.push_back(o[i].first);
        x_compress.push_back(o[i].second);
        l.insert(o[i].second);
        r.insert(o[i].first);
    }
    sort(all(x_compress));
    unique(all(x_compress));
    int sz = x_compress.size();
    vector<int>ans(n + 1);
    for (int i = 0; i < n; i++) {
        int l1 = lower_bound(all(x_compress), o[i].first) - x_compress.begin();
        int r1 = upper_bound(all(x_compress), o[i].second) - x_compress.begin();
        upd(0, 0, sz, l1, r1, 1);
    }
    for (int i = 0; i <= tree[0]; i++) {
        ans[i] = 0;
    }
    int lst = tree[0] + 1;
    int t = 0;
    while (l.size()) {
        int l1 = *l.begin();
        int r1 = *r.rbegin();
        if (l1 < r1) {
            l1 = upper_bound(all(x_compress), l1) - x_compress.begin();
            r1 = lower_bound(all(x_compress), r1) - x_compress.begin();
            if (l1 < r1) {
                upd(0, 0, sz, l1, r1, 2);
            }
            if (l1 <= r1) {
                upd(0, 0, sz, l1 - 1, l1, 1);
                upd(0, 0, sz, r1, r1 + 1, 1);
            }
        }
        t++;
        for (; lst <= tree[0]; lst++) {
            ans[lst] = t;
        }
        l.erase(l.begin());
        r.erase(*r.rbegin());
    }
    for (int i = 0; i < q; i++) {
        cin >> t;
        cout << ans[t] << endl;
    }
}

signed main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    solve();
    return 0;
}