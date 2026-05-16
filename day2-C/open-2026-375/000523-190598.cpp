#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll

#pragma gcc optimize("O3")
#pragma gcc target("avx3,avx2")

using pii = pair<int, int>;

void solve(){
    int n,  q;
    cin >> n >> q;
    int t;
    for(int i = 0; i < n; i++){
        cin >> t >> t;
    }
    while(q--){
        int x;
        cin >> x;
        cout << x << '\n';
    }
    cout << '\n';
}

signed main(){
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}