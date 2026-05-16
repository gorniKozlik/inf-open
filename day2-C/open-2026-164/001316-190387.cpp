#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define ub upper_bound
#define lb lower_bound
#define pll pair<ll, ll>

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

const ll INF = 1e18;

ll t[800100];
ll lz[800100];
pll a[200100];

ll n;

set<pll> scan;

void push(ll v, ll l, ll r) {
    if (lz[v] == 0)
        return;
    if (l + 1 == r) {
        lz[v] = 0;
        return;
    }
    lz[v * 2 + 1] = max(lz[v * 2 + 1], lz[v]);
    lz[v * 2 + 2] = max(lz[v], lz[v *2 + 2]);
    t[v * 2 + 1] = max(lz[v], t[v * 2 + 1]);
    t[v * 2 + 2] = max(lz[v], t[v * 2 + 2]);
    lz[v] = 0;
}

void add(ll lx, ll rx, ll x, ll v = 0, ll l = 1, ll r = n + 1) {
    if (lx >= r || rx <= l)
        return;
    push(v, l, r);
    if (lx <= l && rx >= r) {
        lz[v] = max(lz[v], x);
        t[v] = max(t[v], x);
        push(v,l,r);
        return;
    }
    ll m = (l + r) / 2;
    add(lx, rx, x, v * 2 + 1, l, m);
    add(lx, rx, x, v * 2 + 2, m, r);
    t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
}

ll get(ll lx, ll rx, ll v = 0, ll l = 1, ll r = n + 1) {
    if (lx >= r || rx <= l)
        return 0;
    push(v, l, r);
    if (lx <= l && rx >= r) {
        return t[v];
    }
    ll m = (l + r) / 2;
    return max(get(lx, rx, v * 2 + 1, l, m), get(lx, rx, v * 2 + 2, m, r));
}

void solve() {
    ll q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i].f >> a[i].s;
        scan.insert({a[i].f, 1});
        scan.insert({a[i].s, -1});
        scan.insert({a[i].s + 1, 0});
    }
    ll cnt = 0;
    ll pref = 0;
    ll suff = 0;
    for (auto to : scan) {
        if (to.s > 0)
            cnt += to.s;
        if (to.s == 0) {
            pref+=2;
            cnt--;
        }
        suff = n * 2 - pref - cnt * 2;
       // cout << cnt << ' ' << to.f << ' ' << suff << ' ' << pref << endl;
        add(1, min(pref, suff) + cnt + 1, cnt);
    }
    for (int i = 0; i < q; i++) {
        ll k;
        cin >> k;
        ll d = get(k, n + 1);
      //  cout << d << endl;
        if (d > k) {
           cout << 0 << ' ';
        }
        else {
           cout << (k - d + 1) / 2 << ' ';
        }
    }
}


signed main() {
    ios_base::sync_with_stdio(0);
    //cin.tie(0);
    ll t = 1;
    //cin >> t;
    while (t--) {
        solve();
        cout << '\n';
    }
    return 0;
}
