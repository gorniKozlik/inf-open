#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <bitset>
#include <cmath>
#include <cstring> 
#include <iostream>
#include <string>
#pragma ivdep
#pragma GCC target("avx2")

typedef long long ll;
using namespace std;
typedef pair<ll, ll> pi;
//namespace __gnu_pbds{
//  typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//}
//using namespace __gnu_pbds;

const ll maxN = 5e5, maxM = 1e3, maxA = 1e6, mod = 1e9 + 7;
ll dp[maxM] = {0}, dpp[maxM] = {0}, a[maxN] = {0}, b[maxM] = {0}, ca[maxN] = {0}, cb[maxN] = {0};
void solve(){
    ll n, m, k, x; cin >> n >> m >> k >> x;
    for (ll i = 0; i  < n ; i++) cin >> a[i] >> ca[i];
    for (ll i = 0; i  <m ; i++) cin >> b[i] >> cb[i];
    for (ll i = 0; i < m; i++) dp[i] = -1;
    dp[0] = x;
    for (ll i = 0; i < n; i++) {
        memcpy(dpp, dp, sizeof(dp));
        memset(dp, 0, sizeof(dp));
        for (ll j = 0; j < m; j++) {
            dp[j] = -1;
            if (b[j] < a[i]) continue;
            dp[j] = dpp[j];
            for (ll k = 0; k < m; k++) {
                dp[j] = max(dp[j], dpp[k] - cb[k]);
            }
            if (dp[j] != -1) dp[j] += ca[i];
        }
    }
    for (ll i = 0; i < m; i++) {
        if (dp[i] > -1) {
            cout << "Yes";
            return;
        }
    }
    cout << "No";
    return;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll T = 1;
    while (T--) {
        solve();
    }
}