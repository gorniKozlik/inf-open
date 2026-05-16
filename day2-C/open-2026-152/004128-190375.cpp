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
    vector<int> ans(q);
    for (int i = 0; i < q; i++) cin >> ans[i];
    int cnt = 0, bl = 0;
    int ind = 0;
    int mn = 1e9;
    vector<array<int, 3>> arr1;
    while (ind < arr.size()) {
        int pr = arr[ind].first;
        while (ind < arr.size() && arr[ind].first == pr) {
            bl -= arr[ind].second;
            if (arr[ind].second == 1) cnt++;
            ind++;
        }
        int l = bl, r = bl + min(n - cnt - bl, cnt) * 2;
        arr1.push_back({l, -1, r});
        arr1.push_back({r + 1, 1, l});
    }
    vector<int> ans1(n + 1);
    sort(arr1.begin(), arr1.end());
    multiset<int> st;
    ind = 0;
    for (int i = 0; i <= n; i++) {
        while (ind < arr1.size() && arr1[ind][0] == i) {
            if (arr1[ind][1] == -1) st.insert(arr1[ind][0]);
            else st.erase(st.find(arr1[ind][2]));
            ind++;
        }
        if (st.size() == 0) ans1[i] = -1;
        else ans1[i] = (i - *st.rbegin() + 1) / 2;
    }
    for (auto i: ans) {
        cout << ans1[i] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
//    cin >> t;
    while (t--) solve();
}

