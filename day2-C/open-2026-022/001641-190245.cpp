#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio();
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> all(n);
    vector<pair<int, int>> ts;
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first >> all[i].second;
        ts.push_back({all[i].first, 1});
        ts.push_back({all[i].second, -1});
    }
    sort(ts.begin(), ts.end());
    vector<int> t1(2 * n), t2(2 * n), t3(2 * n);
    vector<int> mx(2 * n);
    int cnt = 0;
    for (int i = 0; i < 2 * n; ++i) {
        t1[i] = i;
        if (ts[i].second == 1) {
            cnt++;
        }
        t2[i] = cnt;
        t3[i] = 2 * n - 1 - i;
        mx[i] = min(t1[i], t3[i]) + 1;
        if (ts[i].second == -1) {
            cnt--;
        }
    }
    set<pair<int, int>> t_ans;
    vector<pair<int, int>> t_del;
    for (int i = 0; i < 2 * n; ++i) {
        t_del.push_back({mx[i], i});
        t_ans.insert({-t2[i], i});
    }
    sort(t_del.begin(), t_del.end());
    vector<pair<int, int>> qs(q);
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        qs[i] = {k, i};
    }
    int l = 0;
    vector<int> ans(q);
    sort(qs.begin(), qs.end());
    for (auto [k, in] : qs) {
        while (l < 2 * n && t_del[l].first < k) {
            int y = t_del[l].second;
            t_ans.erase({-t2[y], y});
            l++;
        }
        int u = t_ans.begin()->second;
        ans[in] = max(0ll, (k + t_ans.begin()->first + 1) / 2);
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}

