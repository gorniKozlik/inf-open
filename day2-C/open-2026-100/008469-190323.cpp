#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1ll<<32;
struct node {
    int x;
    int type;
};
bool comp(node &n1, node &n2) {
    return n1.x < n2.x;
}
struct Node {
    int l = -1, r = -1;
    int mxv = 0, add = 0;
};
void push(vector<Node> &t, int ind) {
    if (t[ind].l == -1) {
        t[ind].l = t.size();
        t.push_back({-1, -1, 0, 0});
    }
    if (t[ind].r == -1) {
        t[ind].r = t.size();
        t.push_back({-1, -1, 0, 0});
    }
    if (t[ind].add == 0) {
        return;
    }
    t[t[ind].l].add += t[ind].add;
    t[t[ind].r].add += t[ind].add;
    t[t[ind].l].mxv += t[ind].add;
    t[t[ind].r].mxv += t[ind].add;
    t[ind].add = 0;
}
void upd(vector<Node> &t, int ind, int l, int r, int ql, int qr, int delta) {
    if (l >= ql and r <= qr) {
        t[ind].mxv += delta;
        t[ind].add += delta;
        return;
    }
    if (l >= qr or r <= ql) {
        return;
    }
    int mid = (l + r) / 2;
    push(t, ind);
    upd(t, t[ind].l, l, mid, ql, qr, delta);
    upd(t, t[ind].r, mid, r, ql, qr, delta);
    t[ind].mxv = max(t[t[ind].l].mxv, t[t[ind].r].mxv);
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    set<int> rs, ls;
    map<int, int> mp1, mp2;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        ls.insert(a[i].first);
        rs.insert(a[i].second);
        mp1[a[i].first] = a[i].second;
        mp2[a[i].second] = a[i].first;
    }
    vector<int> ans(n + 1);
    vector<Node> t(1, {-1, -1, -inf, 0});
    for (int i = 0; i < n; i++) {
        upd(t, 0, 0, inf, a[i].first, a[i].second + 1, 1);
    }
    int z = t[0].mxv;
    int add = 0;
    while (z + add != n) {
        int mnr = *rs.begin();
        int l1 = mp2[mnr], r1 = mnr;
        int mxl = *ls.rbegin();
        int l2 = mxl, r2 = mp1[mxl];
        rs.erase(r1);
        rs.erase(r2);
        ls.erase(l1);
        ls.erase(l2);
        upd(t, 0, 0, inf, l1, r1 + 1, -1);
        upd(t, 0, 0, inf, l2, r2 + 1, -1);
        ans[z + add + 1]++;
        z = t[0].mxv;
        add += 2;
    }
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

