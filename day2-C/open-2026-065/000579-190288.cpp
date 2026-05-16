#include <bits/stdc++.h>
//#include <bits/extc++.h>
using namespace std;
//using namespace __gnu_pbds;
using ll = long long;
using ld = long double;
using pii = pair<ll, ll>;
using pic = pair<ll, char>;
using ull = unsigned long long;
//using oset = tree<ll, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937 rnd('S' + 'E' + 'E' + 'D');
ll l_r(const ll &lb_, const ll &rb_) {return (lb_ + rnd() % (rb_ - lb_ + 1)); }
template<class T> ll szl(const T &v1) { return (ll)v1.size(); }
template<class T> bool mmin(T &v1, const T &v2) { return (v1 > v2 ? v1 = v2, 1 : 0); }
template<class T> bool mmax(T &v1, const T &v2) { return (v1 < v2 ? v1 = v2, 1 : 0); }
#ifndef MiracleFFT
    #pragma GCC optimize("O3,unroll-loops")
    #pragma GCC target("avx,avx2,bmi,bmi2,lzcnt,popcnt")
#endif
const ll INF = 2e9 + 10;
const ll LNF = 2e18 + 10;
const ll MAXN = 2e5 + 10;
const ll MAXX = 1e9 + 10;
const ll MAXC = 1e18 + 10;
const ll ALPH = 26;
const ll BL_SZ = 400;
const ll MAX_LOG = 20;
const ll CNT_OP = 100;
const ll MOD = 1e9 + 7;
const ll P = 179;
const ll M = 1e9 + 787;
const ld UNO = ld(1.0);
const ld PI = atan2(0, -1);
const ld BURN = ld(0.99999);


void solve() {
    ll n, q;
    cin >> n >> q;

    vector<ll> all, lb, rb;
    vector<pii> a(n);
    for (auto &[l, r] : a) {
        cin >> l >> r;
        all.push_back(l);
        all.push_back(r);
        lb.push_back(l);
        rb.push_back(r);
    }

    sort(all.begin(), all.end());
    all.resize(unique(all.begin(), all.end()) - all.begin());
    sort(lb.begin(), lb.end());
    sort(rb.begin(), rb.end());

    vector<ll> s(szl(all) + 1);
    for (auto [l, r] : a) {
        l = lower_bound(all.begin(), all.end(), l) - all.begin();
        r = lower_bound(all.begin(), all.end(), r) - all.begin();
        s[l + 1]++;
        s[r + 1]--;
    }
    for (ll i = 1; i < szl(all); i++) {
        s[i] += s[i - 1];
    }

    ll u1 = 0;
    ll u2 = 0;

    ll out = -1;
    vector<ll> r(n + 1, -LNF);
    for (ll i = 0; i < szl(all); i++) {
        while (u1 < n && rb[u1] < all[i]) {
            u1++;
        }
        while (u2 < n && lb[u2] < all[i]) {
            u2++;
        }

        ll c = min(u1, n - u2);
        mmax(out, s[i]);
        for (ll j = s[i] + 1; j <= min(n, s[i] + c * 2); j++) {
            mmax(r[j], s[i]);
        }
    }

    while (q--) {
        ll x;
        cin >> x;
        if (x <= out) {
            cout << "0 ";
            continue;
        }
        cout << (x - r[x] + 1) / 2 << ' ';
    }
    cout << '\n';
}


int main() {
    bool IS_MULTITEST = 0; 
    #ifdef MiracleFFT
        IS_MULTITEST = 1;
        freopen("ain.txt", "r", stdin);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(9) << fixed;
    //prep();
    ll t = 1;
    if (IS_MULTITEST) {
        cin >> t;
    }
    while (t--) {
        solve();
    }
    #ifdef MiracleFFT
        cout << setprecision(2) << fixed;
        cout << "Time: " << ((ld)clock() / CLOCKS_PER_SEC) << " Sec" << endl;
    #endif
}
