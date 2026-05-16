#include "bits/stdc++.h"

using namespace std;

#ifdef OG_Matveychick1
bool local = 1;
#else
bool local = 0;
#endif


#define ret return
#define con continue
#define be(x) x.begin()
#define en(x) x.end()
#define all(x) be(x), en(x)
#define pb push_back
#define fi first
#define se second
#define ba(x) x.back()
#define pob pop_back
#define for0(i, n) for (ll i = 0; i < n; i++)
#define rfor0(i, n) for (ll i = n - 1; i >= 0; i--)
#define rep(i, a, n) for (ll i = a; i < n; i++)
#define for1(i, n) for (ll i = 1; i < n; i++)
#define rfor1(i, n) for (ll i = n - 1; i >= 1; i--)
#define sz(x) x.size()
#define rev reverse
#define rs resize
#define endl '\n'
#define lb lower_bound
typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
typedef vector<pair<ll, ll> > vpll;
typedef string str;
typedef set<ll> sll;
typedef vector<vector<ll> > vvll;
typedef set<pll> spll;
typedef vector<char> vc;
typedef vector<vector<char> > vvc;
typedef vector<str> vs;
typedef queue<ll> qll;

mt19937_64 rn(chrono::steady_clock::now().time_since_epoch().count());

ll rnd(ll l, ll r) {
    ret rn() % (r - l + 1) + l;
}

void solve();

signed main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.precision(12);
    cout << fixed;
    if (local) {
        freopen("input.txt", "r", stdin);
    }
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}


const ll N = 1e6 + 5;

ll n, q, a[N], b[N], c[2 * N], cl[2 * N], cr[2 * N], mx0, a10[N], a11[N], a2[N];
vll s{0};
vpll u10[N], u11[N], u2[N];

void update1(ll L, ll cnt) {
    if (L % 2 == 0) {
        u10[L / 2].pb({1, 1});
        u10[L / 2 + cnt].pb({-1, 1 + cnt});
    } else {
        u11[L / 2].pb({1, 1});
        u11[L / 2 + cnt].pb({-1, 1 + cnt});
    }
}

void update2(ll L, ll cnt, ll x) {
    u2[L].pb({1, x});
    u2[L + cnt].pb({-1, x + cnt});
}

void update(ll L, ll x, ll R) {
    mx0 = max(mx0, x);
    update1(x + 1, min(L, R));
    update2(x + 1 + 2 * min(L, R), max(L, R) - min(L, R), min(L, R) + 1);
}

void build(vpll *u, ll *a) {
    ll ad = 0;
    multiset<ll> s{(ll) 1e18};
    for0(i, N) {
        for (auto [tp, x]: u[i]) {
            if (tp == 1) s.insert(x - ad);
            else s.erase(s.find(x - ad));
        }
        a[i] = *be(s) + ad;
        ad++;
    }
}

void solve() {
    cin >> n >> q;
    for0(i, n) cin >> a[i] >> b[i];
    for0(i, n) s.pb(a[i]), s.pb(b[i]);
    sort(all(s));
    for0(i, n) a[i] = lb(all(s), a[i]) - be(s);
    for0(i, n) b[i] = lb(all(s), b[i]) - be(s);
    for0(i, n) cl[0]++, cl[a[i]]--, cr[b[i] + 1]++, c[a[i]]++, c[b[i] + 1]--;
    partial_sum(c, c + N, c);
    partial_sum(cl, cl + N, cl);
    partial_sum(cr, cr + N, cr);
    for0(i, N) {
        update(cl[i], c[i], cr[i]);
    }
    build(u10, a10);
    build(u11, a11);
    build(u2, a2);
    while (q--) {
        ll k;
        cin >> k;
        cout << (k <= mx0 ? 0 : min({a10[k / 2], a11[(k - 1) / 2], a2[k]})) << ' ';
    }
}
