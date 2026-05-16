
#include <bits/stdc++.h>
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2")
#define int int64_t
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;

const int N = 5e5 + 100, INF = 1e15;

int cost[N], dp[N], pref[N];

int32_t main() {
    for (int i = 0; i < N; i++)
        cost[i] = INF, dp[i] = -INF;


    cin.tie(0)->sync_with_stdio(0);
    
    int n, m, k, x; cin >> n >> m >> k >> x;
    vector<pair<int, int>> a(n);

    vector<int> b;
    for (auto &[l, r] : a)
        cin >> l >> r, b.push_back(l);

    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] + a[i].second;

    sort(all(b));
    b.erase(unique(all(b)), b.end());

    for (int i = 0; i < n; i++) {
        a[i].first = lower_bound(all(b), a[i].first) - b.begin();
    }

    while (m--) {
        int l, r; cin >> l >> r;
        int id = upper_bound(all(b), l) - b.begin() - 1;
        if (id >= 0)
            cost[id] = min(cost[id], r);
    }

    for (int i = N - 2; i >= 0; i--)
        cost[i] = min(cost[i], cost[i + 1]);


    dp[0] = x;
    
    vector<int> st;


    for (int i = 1; i <= n; i++) {
        while (!st.empty() && a[i - 1].first >= a[st.back()].first)
            st.pop_back();

        if (st.empty()) {
            if (cost[a[i - 1].first] >= dp[0])
                dp[i] = max(dp[i], dp[0] - cost[a[i - 1].first] + pref[i]);
        } else {
            if (cost[a[i - 1].first] >= dp[st.back() + 1])
                dp[i] = max(dp[i], dp[st.back() + 1] - cost[a[st.back()].first] - pref[st.back()] + pref[i]);
        }
    }


    if (dp[n] >= 0)
        cout << "Yes";
    else
        cout << "No";
}