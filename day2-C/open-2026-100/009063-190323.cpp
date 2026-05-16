#include <bits/stdc++.h>
using namespace std;
//#define int long long
struct node {
    int x;
    int type;
};
bool comp(node &n1, node &n2) {
    return n1.x < n2.x;
}
struct Node {
    int mxv = 0, add = 0;
};
void push(vector<Node> &t, int ind) {
    if (t[ind].add == 0) {
        return;
    }
    t[ind * 2].add += t[ind].add;
    t[ind * 2 + 1].add += t[ind].add;
    t[ind * 2].mxv += t[ind].add;
    t[ind * 2 + 1].mxv += t[ind].add;
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
    upd(t, ind * 2, l, mid, ql, qr, delta);
    upd(t, ind * 2 + 1, mid, r, ql, qr, delta);
    t[ind].mxv = max(t[ind * 2].mxv, t[ind * 2 + 1].mxv);
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    set<int> rs, ls;
    vector<int> mp1(2 * n + 2), mp2(2 * n + 2);
    set<int> vls;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        vls.insert(a[i].first);
        vls.insert(a[i].second);
    }
    vector<int> vals;
    for (auto i : vls) {
        vals.push_back(i);
    }
    int h = 0;
    while (1<<(++h) < (vals.size()));
    vector<Node> t(1 << (h + 1));
    for (int i = 0; i < n; i++) {
        a[i].first = lower_bound(vals.begin(), vals.end(), a[i].first) - vals.begin();
        a[i].second = lower_bound(vals.begin(), vals.end(), a[i].second) - vals.begin();
        ls.insert(a[i].first);
        rs.insert(a[i].second);
        mp1[a[i].first] = a[i].second;
        mp2[a[i].second] = a[i].first;
    }
    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++) {
        upd(t, 1, 0, 1<<h, a[i].first, a[i].second + 1, 1);
    }
    int z = t[1].mxv;
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
        upd(t, 1, 0, 1<<h, l1, r1 + 1, -1);
        upd(t, 1, 0, 1<<h, l2, r2 + 1, -1);
        ans[z + add + 1]++;
        z = t[1].mxv;
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

