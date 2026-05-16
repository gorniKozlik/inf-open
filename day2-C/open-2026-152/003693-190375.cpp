#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pb push_back


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> arr;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        arr.push_back({l, -1});
        arr.push_back({r, 1});
    }
    sort(arr.begin(), arr.end());
    vector<int> s(q);
    for (int i = 0; i < q; i++) cin >> s[i];
    int cnt = 0, bl = 0;
    int ind = 0;
    int mn = 1e9;
    while (ind < arr.size()) {
        int pr = arr[ind].first;
        while (ind < arr.size() && arr[ind].first == pr) {
            bl -= arr[ind].second;
            if (arr[ind].second == 1) cnt++;
            ind++;
        }
        if (cnt == n - cnt - bl) mn = min(mn, cnt);
    }
    cout << mn;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
//    cin >> t;
    while (t--) solve();
}

