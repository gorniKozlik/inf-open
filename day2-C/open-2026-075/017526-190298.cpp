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

struct event{
    int x, t;
};

void solve(){
    int n, q;
    cin >> n >> q;
    vector<event> events;
    for (int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        events.push_back({l, 1});
        events.push_back({r, -1});
    }
    sort(all(events), [](event a, event b){
        return a.x < b.x;
    });
    vector<int> ans(n + 1, 1e9);
    int cnt_close = 0, bal = 0, cnt_not_open = n;
    for (int i = 0; i < events.size(); i++){
        bal += events[i].t;
        if (events[i].t == -1){
            cnt_close++;
        }
        if (events[i].t == 1){
            cnt_not_open--;
        }
        for (int j = 0; j <= bal; j++){
            ans[j] = 0;
        }
        int idx = bal + 1, cnt = 1;
        for (int j = 0; j < min(cnt_close, cnt_not_open); j++){
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
    for (int i = 0; i < q; i++){
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
