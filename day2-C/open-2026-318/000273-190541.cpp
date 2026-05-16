#include<bits/stdc++.h>

using namespace std;
#define int long long

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    vector<int> k(q);
    for (int i = 0; i < q; i++) cin >> k[i];
    vector<int> l2(200067, 0);
    l2[1] = 0;
    for (int i = 0; i < l2.size(); i++) {
        l2[i] = l2[i / 2] + 1;
    }
    for (int i = 0; i < q; i++) {
        int res = l2[k[i]];
        cout << res << '\n';
    }
    return 0;
}