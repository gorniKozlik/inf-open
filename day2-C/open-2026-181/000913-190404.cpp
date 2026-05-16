#pragma GCC optimize("O3, unroll-loops")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

const int inf = 1e9L;
const int mod = 998244353;
const int maxn = 2e5L + 10;


struct segtree {
    vector<ll> t;
    vector<ll> lazy;
    segtree() {
        lazy.assign(4 * maxn, inf);
        t.assign(4 * maxn, inf);
    }

    inline void apply(int v, int l, int r, int val) {
        t[v] = min(t[v], val);
        lazy[v] = min(lazy[v], val);
    }

    inline void push(int v, int l, int r) {
        if (lazy[v] == inf || r - l == 1) return;
        int mid = l + (r - l) / 2;
        apply(2 * v + 1, l, mid, lazy[v]), apply(2 * v + 2, mid, r, lazy[v]);
        lazy[v] = inf;
    }

    int get_min(int v, int l, int r, int lx, int rx) {
        push(v, l, r);
        if (l >= lx && r <= rx) return t[v];
        if (l >= rx || r <= lx) return inf;
        int mid = l + (r - l) / 2;
        return min(get_min(2 * v + 1, l, mid, lx, rx), get_min(2 * v + 2, mid, r, lx, rx));
    }

    void make_min(int v, int l, int r, int lx, int rx, int val) {
        if (l >= lx && r <= rx) {
            apply(v, l, r, val);
            return;
        }
        if (l >= rx || r <= lx) return;
        push(v, l, r);
        int mid = l + (r - l) / 2;
        make_min(2 * v + 1, l, mid, lx, rx, val), make_min(2 * v + 2, mid, r, lx, rx, val);
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> arr(n);
    vector<int> xx;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
        xx.emplace_back(arr[i].first); xx.emplace_back(arr[i].second);
    }
    sort(all(xx)); xx.resize(unique(all(xx)) - xx.begin());
    vector<pair<int, int>> events;
    for (auto &[l, r]: arr) {
        l = lower_bound(all(xx), l) - xx.begin();
        r = lower_bound(all(xx), r) - xx.begin();
        events.emplace_back(l, 1);
        events.emplace_back(r, 0);
    }
    sort(all(events));
    ll cnt = 0, dolg = 0;
    segtree t;
    for (int i = 0; i < 2 * n; ++i) {
        auto [x, type] = events[i];
        if (i >= n) {
            if (type) {
                cnt--;
            }else {
                dolg--;
            }
        }else {
            if (type) {
                cnt++;
            }else {
                cnt--;
                dolg += 2;
            }
        }
        t.make_min(0, 0, maxn, max(cnt, 0ll), max(cnt, 0ll) + 1, 0);
        for (int j = 2; j <= dolg; j += 2) {
            t.make_min(0, 0, maxn, max(cnt, 0ll) + j, max(cnt, 0ll) + j + 1, j / 2);
        }
    }
    for (int _ = 0; _ < q; ++_) {
        int k;
        cin >> k;
        cout << t.get_min(0, 0, maxn, k, k + 1) << " ";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
}