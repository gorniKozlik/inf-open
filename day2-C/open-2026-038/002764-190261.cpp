#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ld = long long;
#define all(v) v.begin(), v.end()
#define int long long

typedef tree <int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int N = 4e5+10;
const long long inf = 1e18+10;

int b[N], ans[N];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        v.push_back({l, 0});
        v.push_back({r, 1});
    }
    sort(all(v));
    int cnt = 0;
    for (int i = 0; i < n*2; i++) {
        if (v[i].second == 0) {
            cnt ++;
        } else {
            cnt--;
        }
        b[i] = cnt;
    }
    int l = n-1, r = n-1;
    int a = b[n-1];
    ans[n] = a;
    for (int i = n-1; i >= 1; i --) {
        l--;
        r++;
        ans[i] = max(ans[i+1], b[l]);
        ans[i] = max(ans[i], b[r]);
    }
    while (q--) {
        int k;
        cin >> k;
        cout << (max(k-ans[k], 0ll)+1)/2 << ' ';
    }
    return 0;
}