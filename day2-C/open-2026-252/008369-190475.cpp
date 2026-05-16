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
    // vector<vector<pii>> add_ans(n + 2), del_ans(2 * n + 2);
    for (auto &x : xs) {
        bool begin = (add[x] != 0);
        bool end = (del[x] != 0);
        if (begin) {
            c2--;
            otrs.insert(x);
            int c = otrs.size();
            // add_ans[1].push_back({0, 0});
            // del_ans[c].push_back({0, 0});
            for (int k = 1; k <= c; k++) {
                ans[k] = min(ans[k], 0ll);
            }
            int cc = min(c1, c2);
            if (cc > 0) {
                for (int k = c + 1; k <= c + 2 * cc; k += 2) {
                    ans[k] = min(ans[k], (k - c + 1) / 2);
                    ans[k + 1] = min(ans[k + 1], (k - c + 1) / 2);
                }
                // add_ans[c + 1].push_back({1, 1});
                // del_ans[c + 2 * k].push_back({c + 1, 1});
            } if (c1 > c2) {
                ans[c + 2 * cc + 1] = min(ans[c + 2 * cc + 1], cc + 1);
            }

        } else {
            int c = otrs.size();
            for (int k = 1; k <= c; k++) {
                ans[k] = min(ans[k], 0ll);
            }
            int cc = min(c1, c2);
            if (cc > 0) {
                for (int k = c + 1; k <= c + 2 * cc; k += 2) {
                    ans[k] = min(ans[k], (k - c + 1) / 2);
                    ans[k + 1] = min(ans[k + 1], (k - c + 1) / 2);
                }
                // add_ans[c + 1].push_back({1, 1});
                // del_ans[c + 2 * k].push_back({c + 1, 1});
            } if (c1 < c2) {
                ans[c + 2 * cc + 1] = min(ans[c + 2 * cc + 1], cc + 1);
            }

            // add_ans[1].push_back({0, 0});
            // del_ans[c].push_back({0, 0});
            // int k = min(c1, c2);
            // if (k > 0) {
                
            // add_ans[c + 1].push_back({1, 1});
            // del_ans[c + 2 * k - 1].push_back({c + 1, 1});
            // }

            otrs.erase(del[x]);
            c1++;
        }
    }
    // for (int i = 0; i <= n; i++) {
    //     for (auto x : add_ans[i]) {
    //         cout << x.first << " " << x.second << "  ";
    //     } cout << "\n";
    //     for (auto x : del_ans[i]) {
    //         cout << x.first << " " << x.second << "  ";
    //     } cout << "\n\n";
    // }
    // multiset<pii> s1, s2;
    // int nulls = 0;
    // for (int i = 0; i <= n; i++) {
    //     for (auto x : add_ans[i]) {
    //         if (x.second == 0) {
    //             nulls++;
    //         } else {
    //             if (i % 2 == 0) {
    //                 s1.insert({1 - i/2, i});
    //             } else {
    //                 s2.insert({1 - i/2, i});
    //             }
    //         }
    //     }
    //     if (nulls >= 1) {
    //         ans[i] = 0;
    //     } else {
    //         int ans1 = INF;
    //         int ans2 = INF;
    //         if (!s1.empty()) {
    //             ans1 = s1.begin()->first + i / 2;
    //         } if (!s2.empty()) {
    //             ans2 = s2.begin()->first + (i - 1) / 2;
    //         }
    //         ans[i] = min(ans1, ans2);
    //     }
    //     for (auto x : del_ans[i]) {
    //         if (x.second == 0) {
    //             nulls--;
    //         } else {
    //             if (x.first % 2 == 0) {
    //                 s1.erase({1 - x.first/2, x.first});
    //             } else {
    //                 s2.erase({1 - x.first/2, x.first});
    //             }
    //         }
    //     }
    // }
    // for (auto x : ans) {
    //     cout << x << " ";
    // }
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