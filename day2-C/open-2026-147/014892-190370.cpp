#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
const int MAXN = 1e5;

struct dot {
    int x, y;
    dot(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator<(dot &o) {
        return (x - o.x ? x < o.x : y < o.y);
    }
};

int32_t main() {
    int n, q; cin >> n >> q;
    vector<dot> a(n); for (auto &i : a) cin >> i.x >> i.y;

    vector<int> qr(q); for (auto &i : qr) cin >> i;
    vector<int> b;
    for (auto &i : a) b.push_back((i.x)), b.push_back((i.y));
    sort(a.begin(), a.end());
    sort(b.begin(), b.end()); b.erase(unique(b.begin(), b.end()), b.end());

    map<int, int> got;
    for (auto &i : a) got[i.x] = lower_bound(b.begin(), b.end(), i.x) - b.begin(), got[i.y] = lower_bound(b.begin(), b.end(), i.y) - b.begin();
    vector<int> vl(b.size()), vl1(b.size()), vl2(b.size());
    int am = 0, cur = 0;
    vector<dot> st;
    for (auto &i : a) st.push_back({i.x, 0}), st.push_back({i.y, 1});
    sort(st.begin(), st.end());
    vector<int> got1(b.size());
    for (auto &i : st) {
        cur += 1 - 2 * i.y;
        if (!got1[got[i.x]]) vl1[got[i.x]] = am;
        am += i.y;
        if (!got1[got[i.x]] || !i.y) vl[got[i.x]] = cur + i.y, got1[got[i.x]] = 1;
    };
    got1.assign(b.size(), 0);
    reverse(st.begin(), st.end()); am = 0;
    for (auto &i : st) {
        if (!got1[got[i.x]]) vl2[got[i.x]] = am, got1[got[i.x]] = 1;
        am += !i.y;
    }
    vector<int> v(b.size()), v1(b.size());
    for (int i = 0; i < b.size(); i++) v[i] = min(vl2[i], vl1[i]), v1[i] = v[i] + vl[i];
    // for (int i = 0; i < b.size(); i++) cout << b[i] << ' ' << vl[i] << ' ' << v[i] << '\n';
    vector<dot> f(b.size());
    vector<int> rs;
    vector<dot> r;
    for (int i = 0; i < b.size(); i++) r.push_back({v[i], i}); sort(r.begin(), r.end());
    int mx = -1e18, lst = b.size();
    vector<int> mx1(b.size());
    for (int i = 0; i < b.size(); i++) mx1[i] = max((i ? mx1[i - 1] : (int)-1e18), v1[r[i].y]);
    for (int i = 0; i <= n; i++) {
        while (lst && r[lst - 1].x < i) lst--, mx = max(mx, vl1[r[lst].y]);
        int cmx = max(mx + i, (lst ? mx1[lst - 1] : (int)-1e18) + (i << 1));
        rs.push_back(cmx);
    }
    for (auto &i : qr) {
        cout << lower_bound(rs.begin(), rs.end(), i) - rs.begin() << ' ';
    }
    return 0;
}