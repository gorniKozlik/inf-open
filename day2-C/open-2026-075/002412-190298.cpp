#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long
#define all(arr) arr.begin(), arr.end()
#define rall(arr) arr.rbegin(), arr.rend()

typedef long long ll;
typedef long double ld;
typedef __int128 lll;

mt19937_64 rnd(0);
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve(){
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i].first >> arr[i].second;
    }
    sort(all(arr));
    vector<int> ans(n + 1, 1e9);
    for (int l = 0; l < n; l++){
        int r;
        {
            int left = l, right = n;
            while (left + 1 < right){
                int mid = (left + right) / 2;
                int left_max = arr[l].first, right_min = arr[l].second;
                for (int i = l; i < right; i++){
                    left_max = max(left_max, arr[i].first);
                    right_min = min(right_min, arr[i].second);
                }
                if (left_max < right_min){
                    left = mid;
                } else {
                    right = mid;
                }
            }
            r = right;
        }
        for (int i = 0; i <= r - l; i++){
            ans[i] = 0;
        }
        int cnt = 1, idx = r - l + 1;
        for (int i = 0; i < min(l, n - r); i++){
            ans[idx] = min(ans[idx], cnt);
            ans[idx + 1] = min(ans[idx + 1], cnt);
            idx += 2;
            cnt++;
        }
        while (idx <= n){
            ans[idx] = min(ans[idx], cnt);
            idx++;
            cnt++;
        }
    }
    while (q--){
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.precision(10);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--){
        solve();
        cout << '\n';
    }
    return 0;
}
