#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

#define sz(a) ll((a).size())
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()

mt19937 rnd(1245);

const ll mod = 1e9 + 7;
const int maxn = 5e5 + 1;
const int logn = 25;
const int inf = 2e9;
const ll INF = 2e18;
const ld eps = 1e-8;
const ld pi = acos(-1);

struct event {
    int x, type;
};

bool cmp(event& a, event& b) {
    return a.x < b.x || (a.x == b.x && a.type > b.type);
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > seg(n), new_seg;
    vector<int> cnt;
    vector<event> events;
    for (int i = 0; i < n; ++i) {
        cin >> seg[i].first >> seg[i].second;
        events.push_back({seg[i].first, 1});
        events.push_back({seg[i].second, -1});
    }
    sort(all(events), cmp);

    int prev = -1;
    int bal = 0;
    int d = 0;
    int mx = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (bal == 0) {
            prev = events[i].x;
        }
        bal += events[i].type;
        if (events[i].type == 1) {
            d++;
        }
        if (bal == 0) {
            cnt.push_back(d);
            mx = max(mx, d);
            d = 0;
            new_seg.push_back({prev, events[i].x});
        }
    }

    vector<int> x(n + 1, inf);
    sort(all(cnt));
    int now = sz(cnt) - 1;
    int ans = 1;
    ll sum = cnt.back();
    for (int i = 0; i < n + 1; ++i) {
        if (i > sum) {
            ans++;
            now--;
            sum += cnt[now];
        }
        x[i] = ans / 2;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << x[k] << '\n';
    }
}


signed main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
}
