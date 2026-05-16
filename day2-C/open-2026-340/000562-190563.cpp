#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using db = double;
using pll = pair<ll ,ll>;
using pii = pair<int, int>;
const ll LINF = 7ll<<60;
const db PI = acos(-1.0);
const ll P = 2777;
const ll MOD2 = 1e9 + 1000 - 7;
const ll MOD = 998244353;

struct segtree {
    int n;
    vector<int> t;
    vector<int> d;

    void push(int ind, int l, int r) {
        if (d[ind] == 0)
            return;
        t[ind] += d[ind];
        if (r - l > 1) {
            d[ind * 2 + 1] += d[ind];
            d[ind * 2 + 2] += d[ind];
        }
        d[ind] = 0;
    }

    segtree(int n) : n(n) {
        t.resize(n * 4);
        d.resize(n * 4);
    }

    void update(int ind, int l, int r, int ql, int qr, int add) {
        push(ind, l, r);
        if (r <= ql || qr <= l)
            return;
        if (ql <= l && r <= qr) {
            d[ind] += add;
            push(ind, l, r);
            return;
        }
        int m =(r + l) / 2;
        update(ind * 2 + 1, l, m, ql, qr, add);
        update(ind * 2 + 2, m, r, ql, qr, add);
        t[ind] = max(t[ind * 2 + 1], t[ind * 2 + 2]);
    }

    void update(int ql, int qr, int add) {
        update(0, 0, n, ql, qr, add);
    }

    ll query(int ind, int l, int r, int ql, int qr) {
        push(ind, l, r);
        if (r <= ql || qr <= l)
            return 0;
        if (ql <= l && r <= qr) {
            return t[ind];
        }
        int m = (r + l) / 2;
        return max(query(ind * 2 + 1, l, m, ql, qr), query(ind * 2 + 2, m, r, ql, qr));
    }

    ll query(int ql, int qr) {
        return query(0, 0, n, ql, qr);
    }
};

ll bpow(ll x, ll step) {
    if (step == 0)
        return 1;
    ll z = bpow(x, step / 2);
    if (step % 2)
        return z * z % MOD * x % MOD;
    return z * z % MOD;
}

void solve() {
    int n, q;
    cin >> n >> q;
    segtree x(2 * n);
    vector<int> what;
    map<int, int> z;
    vector<pii> qq(n);
    for (int i = 0; i < n; i++) {
        cin >> qq[i].first >> qq[i].second;
        what.push_back(qq[i].first);
        what.push_back(qq[i].second);
    }
    sort(what.begin(), what.end());
    for (int i = 0; i < what.size(); i++) {
        z[what[i]] = i;
    }
    for (auto el : qq) {
        x.update(z[el.first], z[el.second], 1);
    }
    while (q--) {
        int k;
        cin >> k;
        if (k == 1) {
            cout << 0<< ' ';
            continue;
        }
        int a = x.query(k - 1, 2 * n - k);
        if (a >= k) {
            cout << 0 << ' ';
            continue;
        }
        int ans = (k - a) / 2;
        if ((k - a) % 2 == 1)
            ans++;
        cout << ans << ' ';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
#ifdef HOLA
    freopen("input.txt", "r", stdin);
#endif
    int _t = 1;
    //cin >> _t;
    while (_t--) {
        solve();
    }
}