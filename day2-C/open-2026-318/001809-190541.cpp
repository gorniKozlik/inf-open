#include<bits/stdc++.h>

using namespace std;
#define int long long

int count(vector<pair<int, int>>& a) {
    vector<pair<int, int>> events;
    for (int i = 0; i < a.size(); i++) {
        events.emplace_back(a[i].first, 1);
        events.emplace_back(a[i].second, -1);
    }
    sort(events.begin(), events.end());
    int cur = 0;
    int res = 0;
    for (auto [x, t]: events) {
        cur += t;
        res = max(res, cur);
    }
    return res;
}

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
    int k;
    cin >> k;
    int ans = 0;
    int curcnt = count(a);
    while (curcnt < k) {
        int bestl = 0;
        int bestr = 1;
        for (int i = 0; i < n; i++) {
            if (a[i].first > a[bestl].first) {
                bestl = i;
            }
            if (a[i].second < a[bestr].second) {
                bestr = i;
            }
        }
        // cout << a[bestl].first << ' ' << a[bestl].second << endl;
        // cout << a[bestr].first << ' ' << a[bestr].second << endl;
        int r1 = a[bestr].second;
        int l1 = a[bestl].first;
        a[bestl].first = r1;
        if (a[bestl].first > a[bestl].second) swap(a[bestl].first, a[bestl].second);
        a[bestr].second = l1;
        if (a[bestr].first > a[bestr].second) swap(a[bestr].first, a[bestr].second);
        // cout << a[bestl].first << ' ' << a[bestl].second << endl;
        // cout << a[bestr].first << ' ' << a[bestr].second << endl;
        curcnt = count(a);
        // cout << curcnt << endl;
        ans ++;
    }
    cout << ans;
    return 0;
}