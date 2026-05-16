#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using ld = long double;

const int INF = 1e9;

vi lx, rx;

int n;

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

    if (k > max(min(x + 1, 2 * n - (x + 1)), min(x, 2 * n - x))) return INF;

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

    vi ans(n + 1, INF);

    vi l(n), r(n);

    vector<pi> events;

    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        events.pb({l[i], 0});
        events.pb({r[i], 2});
        events.pb({l[i], 1});
        events.pb({r[i], 1});
    }

    lx.resize(2 * n);
    rx.resize(2 * n);

    sort(events.begin(), events.end());

    int cur = 0;
    int used = 0;
    int closed = 0;

    vi pokr(2 * n);

    int curid = 0;

    vector<pair<pi, int>> qs;

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
            pokr[id] = cur;
            ans[cur] = 0;
            lx[id] = closed;
            rx[id] = n - used;
            qs.pb({{pokr[id], min(lx[id], rx[id])}, id});
        }
    }

    int lst = 0;

    sort(qs.rbegin(), qs.rend());

    for (int i = 0; i < qs.size(); ++i) {
        auto [info, id] = qs[i];
        auto [p, mn] = info;

        for (int j = lst; j <= p + 2 * mn; ++j) {
            ans[j] = min(ans[j], f(j, id));
        }

        lst = max(lst, p + 2 * mn + 1);
    }

    vector<vi> open(n + 1), close(n + 1);

    for (int i = 0; i < 2 * n; ++i) {
        int mx = max(min(i + 1, 2 * n - (i + 1)), min(i, 2 * n - i));
        open[mx].pb(i);
        close[pokr[i] + 2 * min(lx[i], rx[i])].pb(i);
    }

    set<pi> st;

    for (int i = n; i >= 1; --i) {
        for (int x : open[i]) {
            int pot = f(i, x);
            pot += n - i;

            st.insert({pot, x});
        }

        for (int x : close[i]) {
            int pot = f(i, x);
            pot += n - i;

            st.erase(st.find({pot, x}));
        }

        if (!st.empty()) {
            auto [vals, id] = *st.begin();
            // auto [diff, id] = pr;
            ans[i] = min(ans[i], f(i, id));
        } else {
            // cout << "E " << i << endl;
        }
    }

    for (int i = n - 2; i >= 0; --i) {
        ans[i] = min(ans[i], ans[i + 1]); 
    }

    for (int id = 0; id < q; ++id) {
        int k;
        cin >> k;

        cout << max((int)0, ans[k]) << ' ';
    }
}