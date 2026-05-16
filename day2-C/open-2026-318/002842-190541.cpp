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
    int curcnt = count(a);
    vector<int> ans;
    ans.push_back(curcnt);
    set<pair<int, int>> sortl;
    set<pair<int, int>> sortr;
    for (int i = 0; i < n; i++) {
        sortl.emplace(a[i].first, i);
        sortr.emplace(a[i].second, i);
    }
    while (curcnt < n) {
        auto itl = --sortl.end();
        auto itr = sortr.begin();
        int bestl = itl->second;
        int bestr = itr->second;
        // for (int i = 0; i < n; i++) {
        //     if (a[i].first > a[bestl].first) {
        //         bestl = i;
        //     }
        //     if (a[i].second < a[bestr].second) {
        //         bestr = i;
        //     }
        // }
        // cout << a[bestl].first << ' ' << a[bestl].second << endl;
        // cout << a[bestr].first << ' ' << a[bestr].second << endl;
        int r1 = a[bestr].second;
        int l1 = a[bestl].first;
        sortl.erase({a[bestl].first, bestl});
        sortl.erase({a[bestr].first, bestr});
        sortr.erase({a[bestl].second, bestl});
        sortr.erase({a[bestr].second, bestr});
        a[bestl].first = r1;
        if (a[bestl].first > a[bestl].second) swap(a[bestl].first, a[bestl].second);
        a[bestr].second = l1;
        if (a[bestr].first > a[bestr].second) swap(a[bestr].first, a[bestr].second);
        // cout << a[bestl].first << ' ' << a[bestl].second << endl;
        // cout << a[bestr].first << ' ' << a[bestr].second << endl;
        sortl.insert({a[bestl].first, bestl});
        sortl.insert({a[bestr].first, bestr});
        sortr.insert({a[bestl].second, bestl});
        sortr.insert({a[bestr].second, bestr});
        curcnt = count(a);


        // cout << curcnt << endl;
        ans.push_back(curcnt);
    }
    // for (int i: ans) cout << i << ' ';
    // cout << endl;
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        auto it = lower_bound(ans.begin(), ans.end(), k);
        cout << it - ans.begin() << '\n';
    }
    return 0;
}