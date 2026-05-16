#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define pii pair<int, int>
#define ff first
#define ss second
#define ld long double
#define pb push_back
#define ins insert
#define int ll

mt19937 rnd(1488);

void solve(){
    int n, q;
    cin >> n >> q;
    vector<pii> sc;
    for (int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        sc.pb({l, -1});
        sc.pb({r + 1, 1});
    }
    sort(all(sc));
    int mx = 0, bal = 0;
    for (auto [x, y]:sc){
        bal -= y;
        mx = max(mx, bal);
    }
    vector<int> ans(n + 2);
    for (int i = mx + 1; i <= n; i += 2){
        ans[i] = ans[i + 1] = (i - mx + 1) / 2;
    }
    while (q--){
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
}

int32_t main(){
    cin.tie(0)->ios_base::sync_with_stdio(0);
    #ifdef podureman
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // podureman
    int _ = 1;
    //cin >> _;
    while (_--){
        solve();
    }
}
