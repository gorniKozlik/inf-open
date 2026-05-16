#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;


#define rep(x) for (int rep_i = 0; rep_i < x; rep_i++)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define int long long
const ll MOD = 998244353;
const ll LINF = 1ll << 61;
const int maxn = 100100;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> str;
    vector<int> c;
    unordered_map<int, int> d;
    rep(n) {
        int l, r;
        cin >> l >> r;
        str.emplace_back(l, r);
        d[l] = 1;
        d[r] = 2;
        c.push_back(l);
        c.push_back(r);
    }
    sort(all(c));
    sort(all(str));
    vector<int> ans(n + 1, LINF);
    int i = 0;
    int cntl = 0, cntr = 0;
    int gcntl = 0;
    for (auto el: str) {
        if (el.first <= c[i]) {
            gcntl++;
            if (el.second <= c[i])
                cntl++;
        } else {
            if (el.second > c[i])
                cntr++;
        }
    }
    while (i < 2 * n) {
        if ((gcntl - cntl) + min(cntl, cntr) * 2 >= 0) {
            int k = (gcntl - cntl) + min(cntl, cntr) * 2;
            ans[k] = min(ans[k], (k - (gcntl - cntl) + 1) / 2);
        }
        i++;
        if (i == 2 * n)
            break;
        if (d[c[i]] == 1) {
            gcntl++;
            cntr--;
        } else {
            cntl++;
        }
    }
    vector<int> suff(n + 1, LINF);
    suff[n] = ans[n];
    for (int i = n - 1; i >= 0; i--)
        suff[i] = min(suff[i + 1], ans[i]);
    rep(q) {
        int k;
        cin >> k;
        cout << suff[k] << ' ';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(6);

    int mult = 1;
    //cin >> mult;
    while (mult--)
        solve();
    return 0;
}
