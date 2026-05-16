#include <bits/stdc++.h>
using namespace std;


#define int long long
#define line cout << "\n"
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define sz(a) (int) a.size()
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define pii pair<int, int>

typedef string str;
typedef long long ll;
typedef long double ld;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> a(n);
    map<int, vector<int>> tx, ty;
    for (auto &u : a) {
        cin >> u.first >> u.second;
        tx[u.first].pb(u.second);
        ty[-u.second].pb(u.first);
    }
    vector<int> ans(n + 1, 1e9);
    multiset<int> st;
    for (auto &u : tx) {
        for (auto &e : u.second) {
            st.insert(e);
        }
        int calc = 0;
        auto it = st.end();
        for (int i = 1; i <= sz(st); i++) {
            --it;
            calc += *it < u.first;
            if (calc > n - sz(st)) {
                break;
            }
            ans[i + calc] = min(ans[i + calc], calc);
        }
    }
    st.clear();
    for (auto &u : ty) {
        for (auto &e : u.second) {
            st.insert(e);
        }
        int calc = 0;
        auto it = st.begin();
        for (int i = 1; i <= sz(st); i++) {
            calc += *it > u.first;
            if (calc > n - sz(st)) {
                break;
            }
            ans[i + calc] = min(ans[i + calc], calc);
            ++it;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}