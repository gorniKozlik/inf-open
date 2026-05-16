#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ff first
#define ss second
#define pb push_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

const int INF = 1e18, MOD = 998244353;


void solve(){
    int q, n; cin >> n >> q;
    vector<pair<int, int>> event(n);
    for (auto &ell: event) cin >> ell.ff >> ell.ss;
    for (int i = 0; i < q; i++){
        int k; cin >> k;
        cout << k / 2 << '\n';
    }
}

signed main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int t = 1; //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
