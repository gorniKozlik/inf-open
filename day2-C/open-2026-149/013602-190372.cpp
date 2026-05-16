#pragma GCC optimize("O3, unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define oset tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#define int long long

const int INF = 1e18;


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q; cin >> n >> q;
    vector<int> ans(n + 1, n);
    vector<int> xs;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        xs.push_back(l + 1);
        xs.push_back(l - 1);
        xs.push_back(l);
        xs.push_back(r + 1);
        xs.push_back(r - 1);
        xs.push_back(r);
        mp[l]++;
        mp[r]--;
    }
    sort(xs.begin(), xs.end());
    xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
    int cl, cm, cr;
    cl = cm = 0;
    cr = n;
    int l, r;
    l = r = 0;
    int mn = n;
    vector<int> os(n + 1, 0);
    for (int x : xs) {
        if (mp[x] == 1) {
            cm++;
            cr--;
        } else if (mp[x] == -1) {
            cl++;
            cm--;
        }
        //cout << x << " " << cl << " " << cm << " " << cr << "\n";
            while (l <= cm) {
                ans[l] = 0;
                l++;
            }
            os[cm + 1] = max(os[cm + 1], min(cl, cr) * 2);
    }
    set<int> st;
    for (int i = 0; i <= n; i++) {
        st.insert(i);
    }
    for (int i = n; i >= 1; i--) {
        int nl, nr;
        nl = i; nr = i + os[i] - 1;
        while (!st.empty()) {
            auto it = st.lower_bound(nl);
            if (it == st.end() || *it > nr) break;
            ans[*it] = min(ans[*it], (*it - nl + 2) / 2);
            st.erase(it);
        }
    }
    while (q--) {
        int i; cin >> i;
        cout << ans[i] << "\n";
    }
}