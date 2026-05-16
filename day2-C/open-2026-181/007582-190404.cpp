#pragma GCC optimize("O3, unroll-loops")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

const int inf = 1e18L;
const int mod = 998244353;
const int maxn = 3e5L + 10;

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
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
        xx.emplace_back(arr[i].first);
        xx.emplace_back(arr[i].second);
    }
    vector<pair<int, bool>> events;
    sort(all(xx)); xx.resize(unique(all(xx)) - xx.begin());
    for (auto& [x, y]: arr) {
        x = lower_bound(all(xx), x) - xx.begin();
        y = lower_bound(all(xx), y) - xx.begin();
        events.emplace_back(x, 0); events.emplace_back(y, 1);
    }
    sort(all(events));
    ll ans = 0;
    ll cnt_seg = 0;
    segtree t;
    deque<pair<int, int>> ev;
    for (int i = 0; i < n; i++) {
        ans += events[i].second;
        if (events[i].second) {
            cnt_seg--;
        }else {
            cnt_seg++;
        }
        ev.emplace_back(cnt_seg, inf);
        ev.emplace_back(cnt_seg + 2 * ans + 1, cnt_seg);
        // for (int j = 1; j <= ans; ++j) {
        //     t.make_min(0, 0, maxn, 0, cnt_seg + 2 * j + 1, j);
        // }
        t.make_min(0, 0, maxn, 0, cnt_seg + 1, 0);
        t.make_min(0, 0, maxn, 0, cnt_seg + 2 * ans + 1, ans);
    }
    // for (int j = 1; j <= ans; ++j) {
    //     t.make_min(0, 0, maxn, 0, cnt_seg + 2 * j + 1, j);
    // }
    // ev.emplace_back(0, inf);
    // ev.emplace_back(cnt_seg + 2 * ans + 1, 0);
    for (int i = n; i < 2 * n; i++) {
        ans -= !events[i].second;
        if (events[i].second) {
            cnt_seg--;
        }else {
            cnt_seg++;
        }
        ev.emplace_back(cnt_seg, inf);
        ev.emplace_back(cnt_seg + 2 * ans + 1, cnt_seg);
        t.make_min(0, 0, maxn, 0, cnt_seg + 1, 0);
        t.make_min(0, 0, maxn, 0, cnt_seg + 2 * ans + 1, ans);
    }
    sort(all(ev));
    multiset<int> mst;
    for (int i = 0; i <= n; ++i) {
        while (!ev.empty() && ev.front().first <= i) {
            auto [x, y] = ev.front();
            ev.pop_front();
            if (y == inf) {
                mst.emplace(x);
            }else {
                mst.erase(mst.find(y));
            }
        }
        if (!mst.empty()) {
            auto it = mst.upper_bound(i);
            --it;
            int x = *it;
            t.make_min(0, 0, maxn, 0, i + 1, (i - x));
        }
    }
    for (int i = 0; i < q; i++) {
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
