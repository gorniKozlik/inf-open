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

const int N = 2e5 + 1;
// const int N = 30;

int n, q;
pii a[N];

struct Event {
    int x;
    int type;
};

int st[2 * N];
int pref[2 * N];
int pref2[2 * N];

int mn2[2 * N];

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
        pref2[i + 1] = pref2[i] + (st[i] * 2 - 1);
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

    mn2[0] = 0;
    for (int i = 0; i <= 2 * n; i++) {
        mn2[i + 1] = max(mn2[i], pref2[i]);
    }

    while (q--) {
        int x;
        cin >> x;

        // cout << x / 2 << " ";

        int ans;
        if (x == n) {
            ans = n - pref[n];
        } else {
            int mx = 1e9;
            // for (int j = x; j <= 2 * n - x; j++) {
            //     int to_change = (x - pref2[j]);

            //     if (to_change < 0) {
            //         mx = 0;
            //         break;
            //     }

            //     mx = min(mx, (to_change + 1) / 2);
            // }
            int cur_mn = mn2[2 * n - x + 1];
            if (x <= cur_mn) {
                mx = 0;
            } else {
                mx = (x - cur_mn + 1) / 2;
            }
            ans = mx;

        }
    
        cout << ans << " ";

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