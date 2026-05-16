#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
constexpr int MAXN  = 2e5 + 5;
void solve(){
    int n;
    cin >> n;
    int q;
    cin >> q;
    vector <int> sp;
    vector <int> l(n);
    vector <int> r(n);
    for (int i = 0; i < n; i++){
        cin >> l[i] >> r[i];
        sp.push_back(l[i]);
        sp.push_back(r[i]);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    sort(sp.begin(), sp.end());
    vector <pair <int, int>> splow(2 * n);
    for (int i = 0; i < 2 * n; i++){
        int a = upper_bound(l.begin(), l.end(), sp[i]) - l.begin();
        int b = upper_bound(r.begin(), r.end(), sp[i]) - r.begin();
        splow[i] = {a, b};
    }
    while (q--){
        int k;
        cin >> k;
        cout << (k + 1) / 2 << '\n';
        continue;
        int ans = n;
        for (int i = 0; i < 2 * n; i++){
            int a = splow[i].first;
            int b = splow[i].second;
            int nd = a - b;
            int x = n - a;
            if (2 * min(x, b) >= k - nd)
                ans = min(ans, max(0, (k - nd + 1) / 2));
        }
        cout << ans << ' ';
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    while (t--){
        solve();
    }
}

