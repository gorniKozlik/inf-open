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
    vector <pair <int, int>> ans(2 * n);
    for (int i = 0; i < 2 * n; i++){
        int a = upper_bound(l.begin(), l.end(), sp[i]) - l.begin();
        int b = upper_bound(r.begin(), r.end(), sp[i]) - r.begin();
        int x = n - a;
        int mx = a - b + 2 * min(x, b);
        int nd = a - b;
        ans[i] = {mx, nd};
    }
    sort(ans.begin(), ans.end());
    vector <int> mx(2 * n);
    vector <int> res(2 * n);
    for (int i = 2 * n - 1; i > -1; i--){
        mx[i] = ans[i].first;
        res[i] = ans[i].second;
        if (i != 2 * n - 1){
            res[i] =  max(res[i], res[i + 1]);
        }
    }
    while (q--){
        int k;
        cin >> k;
        int i = lower_bound(mx.begin(), mx.end(), k) - mx.begin();
        int nw = res[i];
        cout << (k - nw + 1) / 2 << ' ';
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


