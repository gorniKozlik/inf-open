// #pragma GCC optimize("Ofast")

#include <iostream>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define all(x) x.begin(), x.end()

#ifdef DEBUG
    #define debug(x) {cout << __func__ << ":" << __LINE__ << " " << #x << " = " << x << "\n";};
    #define debugw(x) {cout << __func__ << ":" << __LINE__ << " " << x << "\n";};
#else
    #define debug(x)
    #define debugw(x)
#endif

// const int N = 2e5 + 1;
const int N = 30;

int n, q;
pii a[N];

struct Event {
    int x;
    int type;
};

int st[2 * N];
int pref[2 * N];

void solve() {
    cin >> n >> q;
    vector<Event> events(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;

        events[2 * i] = {a[i].first, 1};
        events[2 * i + 1] = {a[i].second, 0};
    }

    sort(all(events), [&](Event &a, Event &b) {
        return (a.x < b.x) || (a.x == b.x && a.type < b.type);
    });

    for (int i = 0; i < 2 * n; i++) {
        st[i] = events[i].type;
    }

    pref[0] = 0;
    for (int i = 0; i < 2 * n; i++) {
        pref[i + 1] = pref[i] + st[i];
    }

    // int k = 0;
    // int cur = 0;
    // for (auto &event: events) {
    //     cur += event.type;
    //     k = max(cur, k);
    // }

    // debug(k);

    // int m = 0;
    // for (int i = 0; i < n; i++) {
    //     if (events[i].type == -1) {
    //         m++;
    //     }
    // }

    // debug(m);

    while (q--) {
        int x;
        cin >> x;

        // cout << x / 2 << " ";

        int mx = 0;
        for (int j = 0; j <= 2 * (n - x); j++) {
            mx = max(mx, pref[j + x] - pref[j]);
        }

        cout << (x - mx) << " ";
    }
    cout << "\n";

    // while (q--) {
    //     int x;
    //     cin >> x;

    //     int ans;
    //     if (x <= k) {
    //         ans = 0;
    //     } else if (x <= n - k) {
    //         ans = (x - k + 1) / 2;
    //     } else {
    //         ans = (n / 2 - k) * 2 + x - (n - k);
    //     }
    //     cout << ans << " ";
    // }
    // cout << "\n";
}

signed main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    // ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // cout << set_precision(8) << fixed;

    // ll T;
    // cin >> T;
    // while (T--) solve();

    solve();
}