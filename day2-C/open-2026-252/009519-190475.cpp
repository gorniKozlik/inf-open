#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using pii = pair<int, int>;


const int MOD = 998244353;
int INF = 1e12;



void solve() {
    int n, q;
    cin >> n >> q;
    vector<pii> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    set<int> xs;
    map<int, int> add, del;
    for (auto [l, r] : a) {
        add[l] = r;
        del[r] = l;
        xs.insert(l);
        xs.insert(r);
    }

    int c1 = 0, c2 = n;
    
    vector<int> ans(3 * n + 1, INF);
    set<int> otrs;
    int mx = 1;
    vector<vector<int>> add_ans(n + 2), del_ans(2 * n + 2);
    for (auto &x : xs) {
        bool begin = (add[x] != 0);
        if (begin) {
            c2--;
            otrs.insert(x);
            int c = otrs.size();
            mx = max(mx, c);
            int cc = min(c1, c2);
            if (cc > 0) {
                add_ans[c + 1].push_back(c + 1);
                del_ans[c + 2 * cc].push_back(c + 1);
            } if (c1 > c2) {
                ans[c + 2 * cc + 1] = min(ans[c + 2 * cc + 1], cc + 1);
            }
        } else {
            int c = otrs.size();
            mx = max(mx, c);
            int cc = min(c1, c2);
            if (cc > 0) {
                add_ans[c + 1].push_back(c + 1);
                del_ans[c + 2 * cc].push_back(c + 1);
            } if (c1 < c2) {
                ans[c + 2 * cc + 1] = min(ans[c + 2 * cc + 1], cc + 1);
            }
            otrs.erase(del[x]);
            c1++;
        }
    }
    for (int i = 1; i <= mx; i++) {
        ans[i] = 0;
    }

    multiset<pii> s0, s1;
    for (int i = 0; i <= n; i++) {
        for (auto x : add_ans[i]) {
            if (i % 2 == 0) {
                s0.insert({1 - i / 2, i});
            } else {
                s1.insert({1 - i / 2, i});
            }
        }
        if (!s0.empty()) {
            ans[i] = min(ans[i], s0.begin()->first + i / 2);
        } if (!s1.empty()) {
            ans[i] = min(ans[i], s1.begin()->first + (i - 1) / 2);
        }
        for (auto x : del_ans[i]) {
            if (x % 2 == 0) {
                s0.erase(s0.find({1 - x / 2, x}));
            } else {
                s1.erase(s1.find({1 - x / 2, x}));
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int k; cin >> k;
        cout << ans[k] << " ";
    }

    
    

}


signed main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

}