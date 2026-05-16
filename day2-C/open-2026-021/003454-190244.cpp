// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()

const int INF = 1e15 + 69;

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2")

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, q, cnt_left, cnt_right, cnt_mid, cur_k;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<pair<int, int>> scanline;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        scanline.push_back({a[i].first, i + 1});
        scanline.push_back({a[i].second, -i - 1});
    }
    sort(all(scanline));
    vector<vector<int>> to_add(2 * n + 1);
    vector<vector<pair<int, int>>> to_del(2 * n + 1);
    cnt_left = 0;
    cnt_right = n;
    cnt_mid = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (scanline[i].second > 0) {
            cnt_right--;
            cnt_mid++;
        } else {
            cnt_mid--;
            cnt_left++;
        }
        to_add[cnt_mid].push_back(i);
        to_del[cnt_mid + min(cnt_left, cnt_right) * 2].push_back({i, cnt_mid});
    }
    vector<int> ans(n + 1, 0);
    set<pair<int, int>> cur_active;
    for (int i = 0; i <= n; i += 2) {
        for (auto num : to_add[i]) {
            cur_active.insert({i, num});
        }
        if (cur_active.size()) {
            ans[i] = (i - (*(--cur_active.end())).first) / 2;
        }
        for (auto [num, cur_ans] : to_del[i]) {
            cur_active.erase({cur_ans, num});
        }
    }
    cur_active.clear();
    for (int i = 1; i <= n; i += 2) {
        for (auto num : to_add[i]) {
            cur_active.insert({i, num});
        }
        if (cur_active.size()) {
            ans[i] = (i - (*(--cur_active.end())).first) / 2;
        }
        for (auto [num, cur_ans] : to_del[i]) {
            cur_active.erase({cur_ans, num});
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for (int i = 0; i < q; i++) {
        cin >> cur_k;
        cout << ans[cur_k] << " ";
    }
    cout << endl;
    return 0;
}
