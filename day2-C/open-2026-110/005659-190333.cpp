#include <bits/stdc++.h>

#define int long long
using ll = long long;
using ld = long double;
using namespace std;

const int INF = 1e18, MAXN = 1e5, mod = 998244353;

void solve();

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        solve();
        cout << "\n";
    }
}

struct node {
    int x, tp;
};

bool cmp(node a, node b) {
    return a.x < b.x;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int,int> > otr(n);
    vector<node> all;
    for (int i = 0; i < n; i++) {
        cin >> otr[i].first >> otr[i].second;
        all.push_back({otr[i].first, 1});
        all.push_back({otr[i].second, 2});
    }
    sort(all.begin(), all.end(), cmp);
    vector<int> ans(n + 1, INF);
    vector<vector<int> > a0(n + 5);
    vector<vector<int> > a1(n + 5);
    int ind = 1;
    int sm = 0, cnt1 = 0, cnt2 = n;
    for (auto [x, tp]: all) {
        if (tp == 1) {
            sm++;
            cnt2--;
        } else {
            sm--;
            cnt1++;
        }
        int mn = min(cnt1, cnt2);

        a0[sm].push_back(ind);
        a1[sm + (mn + 1) * 2].push_back(ind);
        ind++;
    }

    int dop0 = 0, dop1 = 0;
    map<int, int> mp;
    set<pair<int,int> > s0, s1;
    for (int i = 0; i <= n; i++) {
        if (i % 2 == 0) {
            for (auto idx: a0[i]) {
                mp[idx] = -dop0;
                s0.insert({-dop0, idx});
            }
            for (auto idx: a1[i]) {
                s0.erase({mp[idx], idx});
            }
            if (!s0.empty()) {
                ans[i] = s0.begin()->first + dop0;
            }

            dop0++;
        } else {
            for (auto idx: a0[i]) {
                mp[idx] = -dop1;
                s1.insert({-dop1, idx});
            }
            for (auto idx: a1[i]) {
                s1.erase({mp[idx], idx});
            }

            if (!s1.empty()) {
                ans[i] = s1.begin()->first + dop1;
            }
            dop1++;
        }
    }
    for (int i = 0; i + 1 <= n; i++) {
        ans[i + 1] = min(ans[i + 1], ans[i] + 1);
    }

    for (int i = n - 1; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }


    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}
