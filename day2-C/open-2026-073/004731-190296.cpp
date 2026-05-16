#include <bits/stdc++.h>
#define int long long

using namespace std;
const int INF = 1e9;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector <pair<int, int>> a(n);

    vector <pair<int, int>> c;

    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        c.push_back({a[i].first, 0});
        c.push_back({a[i].second, 1});
    }

    sort(c.begin(), c.end());

    int left = 0;
    int cnt = 0;
    vector <int> ans(n + 1, INF);

    ans[0] = 0;
    vector <int> p(n + 1);
    for (auto [i, type] : c) {
        int right = n - left - cnt;
        int k = min(left, right);

        p[cnt] = max(p[cnt], k);
        ans[cnt] = 0;

        if (type == 0) {
            cnt++;
        }
        else {
            cnt--;
            left++;
        }

        right = n - left - cnt;
        k = min(left, right);

        p[cnt] = max(p[cnt], k);
        ans[cnt] = 0;
    }

    set <pair<int, int>> s;
    for (int i = 0; i <= n; ++i) {
        if (ans[i] == 0) {
            s.insert({i, i + 2 * p[i]});
            continue;
        }

        pair <int, int> cur;
        while (true) {
            auto it = s.end();
            it--;

            cur = *it;

            if (i <= cur.second) {
                break;
            }
            else {
                s.erase(it);
            }
        }

        int d = (i - cur.first + 1) / 2;
        ans[i] = d;
    }

    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;

        cout << ans[x] << " ";
    }

    return 0;
}