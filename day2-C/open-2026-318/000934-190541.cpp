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
    vector<int> l;
    for (auto [x, y]: a) {
        l.push_back(x);
        l.push_back(y);
    }
    int mid = l[l.size() / 2];
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].second < l[mid]) cnt++;
        else if (a[i].first >= l[mid]) cnt++;
    }
    cout << (cnt + 1) / 2 << endl;
    // for (int i = 0; i < q; i++) {
    //     int l = -1, r = 4e5;
    //     while (r - l > 1) {
    //         int m = (l + r) / 2;
    //         if (2 * m + (2 * m < n) < k[i]) l = m;
    //         else r = m;
    //     }
    //     cout << r << '\n';
    // }
    return 0;
}