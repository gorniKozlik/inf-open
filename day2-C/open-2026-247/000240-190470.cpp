#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define ff first
#define ss second
#define rs resize
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define int long long

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double ld;

template<typename T, typename T1>
istream& operator >>(istream &in, pair<T, T1> &a) {
    in >> a.ff >> a.ss;
    return in;
}

template<typename T, typename T1>
ostream& operator <<(ostream &out, pair<T, T1> &a) {
    out << a.ff << " " << a.ss;
    return out;
}

template<typename T>
istream& operator >>(istream &in, vector<T> &a) {
    for (auto &i : a) in >> i;
    return in;
}

template<typename T>
ostream& operator <<(ostream &out, vector<T> &a) {
    for (auto i : a) out << i << " ";
    return out;
}

void solve() {
    int n, q; cin >> n >> q;

    vector<pii>  st;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        l--; r--;

        st.pb({l, -1});
        st.pb({r, 1});
    }
    sort(all(st));

    vector<pii> kr;
    int ot = 0, zk = 0;
    for (auto [a, b] : st) {
        kr.pb({ot + min(zk, n - ot - zk) * 2, min(zk, n - ot - zk)});
        if (b == -1) ot++;
        kr.pb({ot + min(zk, n - ot - zk) * 2, min(zk, n - ot - zk)});
        if (b == 1) ot--, zk++;
    }
    sort(all(kr));

    vector<int> ans(n + 2, 1e9);
    int j = sz(kr) - 1;
    for (int i = n; i > -1; i--) {
        ans[i] = ans[i + 1];
        while (j > -1 && kr[j].ff >= i) {
            ans[i] = min(ans[i], kr[j].ss);
            j--;
        }
    }

    while (q--) {
        int a; cin >> a;

        cout << max(0LL, ans[a]) << "\n";
    }
}

int32_t main() {
#ifdef LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    int test = 1;
    //cin >> test;
    while (test--) {
        solve();
    }
}