#include <bits/stdc++.h>

#define all(a) a.begin(), a.end()

using namespace std;

using ll = long long;
using pii = pair<int, int>;

const int inf = 1e9;
const ll INF = 1e18;

const int mod = 998'244'353;

void ban() {
    cout << "No" << '\n';
    exit(0);
}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<ll> cords;
    vector<pii> segs(n);
    for (int i = 0; i < n; ++i) {
        cin >> segs[i].first >> segs[i].second;
        cords.push_back(segs[i].first);
        cords.push_back(segs[i].second);
        // cords.push_back(segs[i].second + 1);
        // cords.push_back(segs[i].second - 1);
    }

    // sort(all(segs));

    sort(all(cords));
    cords.resize(unique(all(cords)) - cords.begin());

    int cnt = 0;
    vector<int> upd(cords.size() + 1);
    vector<int> upd2(cords.size() + 1);
    for (int i = 0; i < n; ++i) {
        int ind1 = lower_bound(all(cords), segs[i].first) - cords.begin();
        int ind2 = lower_bound(all(cords), segs[i].second) - cords.begin();
        ++upd[ind1];
        --upd[ind2 + 1];
        ++upd2[ind2 + 1];
    }

    int sum = 0;
    int sz = cords.size();
    vector<vector<int>> del(n + 2);
    multiset<ll> st;
    for (int i = 0; i < cords.size(); ++i) {
        sum += upd[i];
        cnt += upd2[i];
        int y = cnt;
        int z = n - cnt - sum;
        int up = sum + min(y, z) * 2;
        st.insert(sum);
        st.insert(sum - 1);

        del[min(up + 1, n + 1)].push_back(sum);
        del[min(up + 2, n + 1)].push_back(sum - 1);
    }

    // st.insert(123);
    int mx;
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int val : del[i]) {
            auto iter = st.find(val);
            if (iter != st.end()) {
                st.erase(st.find(val));
            }
        }


        int mx = *(--st.end());

        ans[i] = max((i - mx + 1) / 2, 0);
    }

    int k;
    while (q--) {
        cin >> k;
        cout << ans[k] << '\n';
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    //cin >> t;

    while (t--) {
        solve();
    }
}