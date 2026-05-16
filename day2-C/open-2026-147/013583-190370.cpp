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
    for (int i = 0; i < b.size(); i++) cout << b[i] << ' ' << vl[i] << ' ' << v[i] << '\n';
    vector<dot> f(b.size());
    vector<int> rs;
    for (int i = 0; i <= n; i++) {
        int mx = 0;
        for (int j = 0; j < b.size(); j++) {
            if (v[i] >= i) mx = max(mx, vl[j] + (i << 1));
            else mx = max(mx, v1[j] + i);
        }
        rs.push_back(mx);
    }
    for (auto &i : qr) {
        for (int j = 0; j < rs.size(); j++) if (rs[j] >= i) { cout << j << ' '; break; }
    }
    return 0;
}