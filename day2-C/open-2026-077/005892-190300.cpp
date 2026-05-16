#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using ld = long double;

const int INF = 1e9;
int n;
vi lx, rx;

int f(int k, int x) {
    // cout << "Eqqq"  << endl;
    int cover = n - lx[x] - rx[x];
    int rest = k - cover;
    
    int val = 0;

    if (2 * min(lx[x], rx[x]) >= rest) {
        val += (rest + 1) / 2;
    } else {
        val += min(lx[x], rx[x]);
        val += rest - 2 * min(lx[x], rx[x]);
    }

    return val;
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> n >> q;

    vi l(n), r(n);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];

    vector<pi> events;

    for (int i = 0; i < n; ++i) {
        events.pb({l[i], 0});
        events.pb({r[i], 2});
        events.pb({l[i], 1});
        events.pb({r[i], 1});
        // events.pb({l[i] + 1, 1});
        // events.pb({r[i] + 1, 1});
        // events.pb({l[i] - 1, 1});
        // events.pb({r[i] - 1, 1});
    }
    
    lx.assign(2 * n, 0);
    rx.assign(2 * n, 0);

    sort(events.begin(), events.end());

    int mx = 0;
    int bst = l[0];
    int cur = 0;

    int used = 0;
    int closed = 0;

    int bdiff = INF;

    int curid = 0;

    // cout << "SC " << endl;

    for (auto [time, type] : events) {
        if (type == 0) {
            ++cur;
            ++used;
        } else if (type == 2) {
            --cur;
            ++closed;
        } else if (type == 1) {
            int id = curid;
            ++curid;

            lx[id] = closed;
            rx[id] = n - used;
        }
    }

    // f(5, 8);
    // return 0;

    // cout << "SC " << endl;
    vi ans(n + 1);

    int sz = 2 * n;

    int ls = 0;
    int rs = 0;

    for (int i = 0; i < n; ++i) {
        if (r[i] < bst) ++ls;
        else ++rs;
    }

    int it = 0;

    vector<pair<pi, int>> srt;

    for (int i = 0; i < lx.size(); ++i) srt.pb({{n - lx[i] - rx[i], min(lx[i], rx[i])}, i});

    sort(srt.begin(), srt.end());

    vector<pair<pi, int>> stk;

    int ssz = lx.size();

    for (int i = 0; i < ssz; ++i) {
        while (!stk.empty()) {
            int v1 = stk.back().first.first;
            int v2 = stk.back().first.second;

            auto [u1, u2] = srt[i].first;

            if ((v1 <= u1) && (v2 <= u2)) stk.pop_back();
            else break;
        }

        stk.pb(srt[i]);
    }

    ssz = stk.size();

    for (int b = 1; b <= n; ++b) {
        while (it < (int)stk.size() - 1) {
            // if (it == 4 && b == 2) {
            //     cout << "F " << f(b, it) << ' ' << f(b, it + 1) << endl;
            // }
            if (f(b, stk[it].second) > f(b, stk[it + 1].second)) ++it;
            else break;
        }

        if (b == 2) {
            // cout << "E " << it << ' ' << f(b) << endl;
        }

        // if (b == 5) {
        //     cout << "i " << stk[it].first.first << ' ' << stk[it].first.second << ' ' << stk[it].second << endl;
        // }
        ans[b] = f(b, stk[it].second);
    }

    // cout << "EE " << f(5, 8) << ' ' << lx[8] << ' ' << rx[8] << endl;

    // cout << "B " << endl;

    for (int id = 0; id < q; ++id) {
        int k;
        cin >> k;

        cout << ans[k] << ' ';
    }
}