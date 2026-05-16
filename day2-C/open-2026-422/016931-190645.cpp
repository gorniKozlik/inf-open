#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("avx2")

#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ff first
#define ss second
#define itn int
#define Auto auto
#define Pair pair<int, int>

const int maxn = 2e5 + 10;
const int logn = 20;
const int B = 300;
const int inf = 4e18;
const int mod = 1e9 + 7;
const int mod1 = 998244353;


#ifdef LOCAL
#define debug(x) cerr << (#x) << ": " << x << endl;
#define debugv(x) cerr << (#x) << ": " << "[ "; for(auto t : x){cerr << t << ' ';} cerr << "]" << endl;
#endif


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> l, r;
    map<int, int> dct;
    vector<Pair > edges;
    vector<Pair > events;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        l.pb(x);
        r.pb(y);
        dct[x] = i, dct[y] = i;
        edges.pb({x, y});
        events.pb({x, -1});
        events.pb({y, 1});
    }
    sort(all(l));
    sort(all(r));
    sort(all(events));
    int ans = 0;
    int cnt = 0;
    for (auto [t, tp]: events) {
        if (tp == 1) {
            ans = max(ans, cnt);
        }
        cnt -= tp;
        ans = max(ans, cnt);
    }
    int p = -1, ansp = inf, ansmin = inf;
    cnt = 0;
    for (auto [t, tp]: events) {
        int cur = cnt;
        cnt -= tp;
        cur = max(cur, cnt);
        if (cur == ans) {
            int cntl = lower_bound(all(r), t) - r.begin();
            int cntr = n - (upper_bound(all(l), t) - l.begin());
            if (ansp == max(cntl, cntr)) {
                if (ansmin < min(cntl, cntr)) {
                    ansp = max(cntl, cntr);
                    ansmin = min(cntl, cntr);
                    p = t;
                }
            }
            if (ansp > max(cntl, cntr)) {
                ansp = max(cntl, cntr);
                ansmin = min(cntl, cntr);
                p = t;
            }
        }
    }
    int cntl = ansmin, cntr = ansp;
    vector<int> itg(n + 1, -1);
    for (int i = 1; i <= ans; ++i) {
        itg[i] = 0;
    }
    int i = ans + 1;
    int prev = 0;
    while (i + 1 <= n && cntl > 0) {
        cntl--;
        cntr--;
        prev++;
        itg[i] = prev;
        itg[i + 1] = prev;
        i += 2;
    }
    while (i <= n && cntr > 0) {
        cntr--;
        prev++;
        itg[i] = prev;
        i++;
    }
    while (q--) {
        int tmp;
        cin >> tmp;
        cout << itg[tmp] << ' ';
    }
}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
    return 0ll;
}
