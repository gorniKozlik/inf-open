#include <bits/stdc++.h>
using namespace std;
#define int long long
struct ev {
    int x, t, id;
    ev () {}
    ev(int x, int t, int id) : x(x), t(t), id(id) {}
};
bool operator<(ev &a, ev &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.t > b.t;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector <ev> scan;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        scan.emplace_back(l, 1, i);
        scan.emplace_back(r, -1, i);
    }
    sort(scan.begin(), scan.end());
    int op = 0, cl = 0;
    int bal = 0;
    vector <pair <int, int>> rev;
    vector <pair <int, int>> ans;
    for (ev e : scan) {
        if (e.t == 1) {
            bal += e.t;
            op++;
            int f = min(n - op, cl);
            int f2 = min(n - op + 1, cl);
            int k = bal;
            if (f2 > f) {
                ans.emplace_back(k + 2 * f + 1, f + 1 );
            }
            rev.emplace_back(f, k);
        } else {
            int f = min(n - op, cl);
            int f2 = min(n - op, cl + 1);
            int k = bal;
            if (f2 > f) {
                ans.emplace_back(k + 2 * f + 1, f + 1 );
            }
            rev.emplace_back(f, k);
            cl++;
            bal += e.t;
        }
    }
    sort(rev.begin(), rev.end());
    int k = 0, p = rev.size();
    for (int t = rev.back().first; t >= 0; --t) {
        while (p > 0 && rev[p - 1].first >= t) {
            k = max(k, rev[p - 1].second);
            --p;
        }
        ans.emplace_back(k + 2 * t, t);
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < q; ++i) {
        int d;
        cin >> d;
        int mans = 1e18;
        for (pair <int ,int > l : ans) {
            if (mans > l.second && l.first >= d) {
                mans = l.second;
            }
        }
        cout <<mans  << ' ';
    }
}
signed main() {
    solve();
    return 0;
}