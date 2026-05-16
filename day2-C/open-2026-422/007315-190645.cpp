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


int get(set<Pair > &points) {
    int ans = 0;
    int cnt = 0;
    for (auto [t, tp]: points) {
        if (tp == 1) {
            ans = max(ans, cnt);
        }
        cnt -= tp;
        ans = max(ans, cnt);
    }
    return ans;
}


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> l, r;
    map<int, int> dct;
    vector<Pair > edges;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        l.pb(x);
        r.pb(y);
        dct[x] = i, dct[y] = i;
        edges.pb({x, y});
    }
    sort(all(l));
    sort(rall(r));
    vector<Pair > ans;
    set<Pair > points;
    for (auto t: l) {
        points.insert({t, -1});
    }
    for (auto t: r) {
        points.insert({t, 1});
    }
    ans.pb({0, get(points)});
    for (int i = 0; i < (n + 1) / 2; ++i) {
        int l1 = l[i], r1 = r[i];
        auto l2 = edges[dct[l1]].ss;
        auto r2 = edges[dct[r1]].ff;
        if (l2 == r1) {
            break;
        }
        points.erase({l2, 1});
        points.erase({r2, -1});
        points.insert({r2, 1});
        points.insert({l2, -1});
        ans.pb({i + 1, get(points)});
    }
    vector<int> itg(n + 1);
    int prev = 0;
    for (auto [i, lst]: ans) {
        for (int j = prev; j <= lst; ++j) {
            itg[j] = i;
        }
        prev = lst + 1;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << itg[k] << ' ';
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
