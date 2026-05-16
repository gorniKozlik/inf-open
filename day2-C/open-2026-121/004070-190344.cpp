#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target ("avx2,bmi")
using namespace std;
// using namespace __gnu_pbds;
#define int long long
// typedef tree<int,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
const int N = 1e6 + 10, mod = 998244353, inf = 1e18;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++)cin >> l[i] >> r[i];
    vector<pair<int,int> > v;
    for (int i = 0; i < n; i++) {
        v.push_back({l[i], i + 1});
        v.push_back({r[i], -i - 1});
    }
    sort(v.begin(), v.end());
    int cnt = n;
    int q = 0, mx = 0, w = 0, mx1 = 0;
    vector<vector<int> > vec;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second > 0) {
            q++;
            cnt--;
        } else q--;
        if (mx < q) {
            mx1 = min(cnt, n - cnt - q);
            mx = q;
            w = i;
        }
        if (mx == q && mx1 < min(cnt, n - q - cnt)) {
            mx1 = max(mx1, min(cnt, n - cnt - q));
            mx = q;
            w = i;
        }
        if (q > 0)vec.push_back({q, min(cnt, n - cnt - q)});
    }
    vector<int> ans1(n + 1, inf);
    deque<vector<int> > vec1, vec2;
    mx1 = 0;
    for (auto k: vec) {
        mx1 = max(mx1, k[0]);
        mx = k[0];
        w = k[1];
        if (w!=0) {
            vec1.push_back({mx + 1, mx + 2 * w});
            vec2.push_back({mx + 2 * w + 1, w + 1});
        }
    }
    for (int i = 1; i <= mx1; i++) {
        ans1[i] = 0;
    }
    deque<vector<int> > v1;
    int j = 0;
    for (auto k: vec1) {
        v1.push_back({k[0], j + 1});
        v1.push_back({k[1] + 1, -j - 1});
        j++;
    }
    sort(v1.begin(), v1.end());
    q = 0;
    set<pair<int,int> > s;
    int i1 = 0;
    vector<int> vvv(vec1.size());
    for (int i = 1; i <= n; i++) {
        while (v1.size() > 0 && v1[0][0] == i) {
            if (v1[0][1] < 0) {
                q--;
                s.erase({vvv[-v1[0][1] - 1], -v1[0][1] - 1});
            } else {
                q++;
                s.insert({i1, v1[0][1] - 1});
                vvv[v1[0][1] - 1] = i1;
                i1++;
            }
            v1.pop_front();
        }
        if (s.size() > 0)ans1[i] = min(ans1[i], (i - vec1[(*s.rbegin()).second][0]) / 2 + 1);
    }
    sort(vec2.begin(), vec2.end());
    int mn = inf;
    int ans = inf;
    for (int i = 1; i <= n; i++) {
        while (vec2.size() > 0 && vec2[0][0] == i) {
            if (vec2[0][1] - vec2[0][0] < mn) {
                mn = vec2[0][1] - vec2[0][0];
                ans = vec2[0][1] - 1;
            }
            vec2.pop_front();
        }
        ans++;
        ans1[i] = min(ans1[i], ans);
    }
    while (m--) {
        int x;
        cin >> x;
        cout << ans1[x] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
