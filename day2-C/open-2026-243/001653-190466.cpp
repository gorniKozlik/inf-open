#include<bits/stdc++.h>

#define ll long long

#define debug(x) cerr << (#x) << '=' << x << '\n';

#define INF 1e9

using namespace std;

struct segtree {
    vector<int> s;
    vector<int> d;
    int n;

    void build(int no) {
        n = (1 << (__lg(no) + 1));
        s.resize(n * 2, 0);
        d.resize(n * 2, 0);
    }

    int get_val(int v) {
        return s[v] + d[v];
    }

    void calc_val(int v) {
        s[v] = max(get_val(v * 2), get_val(v * 2 + 1));
    }

    void add(int v, int l, int r, int val, int vl, int vr) {
        if ((r < vl) || (vr < l)) return;
        if ((l <= vl) && (vr <= r)) {
            d[v] += val;
            return;
        }
        int m = (vl + vr) / 2;
        add(v * 2, l, r, val, vl, m);
        add(v * 2 + 1, l, r, val, m + 1, vr);
        calc_val(v);
    }

    int get(int v, int l, int r, int vl, int vr) {
        if ((r < vl) || (vr < l)) return 0;
        if ((l <= vl) && (vr <= r)) {
            return get_val(v);
        }
        int m = (vl + vr) / 2;
        return max(get(v * 2, l, r, vl, m), get(v * 2 + 1, l, r, m + 1, vr));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    int c1 = 0, c2 = 0;
    vector<int> vc(n * 2, 0);
    vector<pair<int, int>> vp(n, {0, 0});
    for (int i = 0; i < n; i++) {
        cin >> c1 >> c2;
        vp[i].first = c1;
        vp[i].second = c2;
        vc[i * 2] = c1;
        vc[i * 2 + 1] = c2;
    }
    sort(vc.begin(), vc.end());
    segtree s;
    s.build(n * 2);
    vector<int> vr(n, 0);
    vector<int> vl(n, 0);
    for (int i = 0; i < n; i++) {
        c1 = lower_bound(vc.begin(), vc.end(), vp[i].first) - vc.begin();
        c2 = lower_bound(vc.begin(), vc.end(), vp[i].second) - vc.begin();
        s.add(1, c1, c2, 1, 0, s.n - 1);
        vl[i] = c1;
        vr[i] = c2;
    }
    sort(vl.begin(), vl.end());
    sort(vr.begin(), vr.end());
    reverse(vr.begin(), vr.end());
    vector<int> res(n + 1, INF);
    c1 = s.get(1, 0, s.n - 1, 0, s.n - 1);
    res[c1] = min(res[c1], 0);
    for (int i = 0; i < n; i++) {
        c1 = vr.back();
        c2 = vl.back();
        vr.pop_back();
        vl.pop_back();
        s.add(1, c1, c2 - 1, 1, 0, s.n - 1);
        s.add(1, c1 + 1, c2, 1, 0, s.n - 1);
        c1 = s.get(1, 0, s.n - 1, 0, s.n - 1);
        res[c1] = min(res[c1], i + 1);
    }
    for (int i = n - 1; i >= 0; i--) {
        res[i] = min(res[i], res[i + 1]);
    }
    for (int i = 0; i < k; i++) {
        cin >> c1;
        cout << res[c1] << ' ';
    }
    cout << '\n';
    return 0;
}