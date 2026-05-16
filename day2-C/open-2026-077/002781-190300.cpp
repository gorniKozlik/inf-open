#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using ld = long double;

const int INF = 1e9;

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vi l(n), r(n);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];

    vector<pi> events;

    for (int i = 0; i < n; ++i) {
        events.pb({l[i], 0});
        events.pb({r[i], 2});
        events.pb({l[i], 1});
        events.pb({r[i], 1});
        events.pb({l[i] + 1, 1});
        events.pb({r[i] + 1, 1});
        events.pb({l[i] - 1, 1});
        events.pb({r[i] - 1, 1});
    }
    
    sort(events.begin(), events.end());

    int mx = 0;
    int bst = l[0];
    int cur = 0;

    int used = 0;
    int closed = 0;

    int bdiff = INF;

    for (auto [time, type] : events) {
        if (type == 0) {
            ++cur;
            ++used;
        } else if (type == 2) {
            --cur;
            ++closed;
        }
        
        if (type == 1) {
            if (cur > mx) {
                mx = cur;
                bst = time;
                int ls = closed;
                int rs = n - used;

                int diff = abs(ls - rs);
                bdiff = diff;
            } else if (cur == mx) {
                int ls = closed;
                int rs = n - used;

                int diff = abs(ls - rs);
                if (diff < bdiff) {
                    mx = cur;
                    bst = time;
                }
            }
        }
    }

    int ls = 0;
    int rs = 0;

    for (int i = 0; i < n; ++i) {
        if (r[i] < bst) ++ls;
        else ++rs;
    }

    // cout << "d " << mx << ' ' << bst << ' ' << bdiff << endl;
    // cout << "L " << ls << ' ' << rs << endl;
    for (int id = 0; id < q; ++id) {
        int k;
        cin >> k;

        if (mx >= k) {
            cout << 0 << ' ';
            continue;
        }

        int rest = k - mx;

        if (2 * min(ls, rs) >= rest) {
            // cout << "EE " << endl;
            cout << (rest + 1) / 2 << ' ';
            continue;
        }

        int spent = min(ls, rs);
        spent += rest - 2 * min(ls, rs);

        cout << spent << ' ';
    }
}