#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;
    vector <pair <int, int>> arr(n);
    vector <int> a;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
        a.push_back(arr[i].first);
        a.push_back(arr[i].second);
    }
    sort(a.begin(), a.end());
    vector <int> ans(n + 1, 1e9);
    for (int x : a) {
        int cnt = 0, l = 0, r = 0;
        int ctl = 0, ctr = 0;
        for (auto p : arr) {
            if (p.first > x) l++;
            else if (p.second < x) r++;
            else {
                if (p.first == x) ctl++;
                if (p.second == x) ctr++;
                cnt++;
            }
        }
        for (int i = 0; i <= cnt; ++i) ans[i] = 0;
        int t = 1;
        for (int i = cnt + 1; i <= cnt + 2 * min(l, r); i += 2) {
            ans[i] = min(ans[i], t);
            ans[i + 1] = min(ans[i + 1], t);
            t++;
        }
        if (l > r) {
            swap(l, r);
            swap(ctl, ctr);
        }
        int now = cnt + 2 * l;
        while (ctl > 0 && r - l > 0) {
            ctl--;
            r--;
            now++;
            ans[now] = min(t, ans[now]);
            t++;
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << endl;
    }
    return 0;
}
