#pragma GCC optimize("O3")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
#define db long double
#define MX LLONG_MAX
#define MN LLONG_MIN
#define gcd __gcd
#define lcm(a, b) (a / gcd(a, b) * b)

using namespace std;
using namespace __gnu_pbds;
using ll = long long;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

//struct node {
//    int l, r;
//};
//
//struct compare_node {
//    bool operator()(const node& a, const node& b) {
//        return a.l < b.l;
//    }
//};

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) cin >> l[i] >> r[i];

    vector<int> vec(2 * n);
    for (int i = 0; i < n; i++) vec[i] = l[i];
    for (int i = 0; i < n; i++) vec[i + n] = r[i];
    sort(vec.begin(), vec.end());

    map<int, int> mp;
    for (int i = 0; i < 2 * n; i++) mp[vec[i]] = i;

    for (auto& x: l) x = mp[x];
    for (auto& x: r) x = mp[x];

    //for (int i = 0; i < n; i++) cout << l[i] << " " << r[i] << "\n";

    vector<bool> used(2 * n, false);
    for (auto x: l) used[x] = true;

    int cur = 0;
    vector<pair<int, int>> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        if (used[i]) cur++;

        int L = i + 1;
        int R = 2 * n - (i + 1);
        int mn = min(L, R);

//        cout << "i = " << i << "\n";
//        cout << "cur = " << cur << "\n";
//        cout << "mn = " << mn << "\n";

        a[i] = {cur, mn};

        if (!used[i]) cur--;
    }
    sort(a.begin(), a.end());

//    cout << "a:\n";
//    for (auto [x, y]: a) cout << x << " " << y << "\n";

    int pos = 0;
    vector<int> ans(n + 1, -52);
    priority_queue<pair<int, int>> pq;
    //priority_queue<node, vector<node>, compare_node> pq;
    for (int i = 1; i <= n; i++) {
        while (pos < 2 * n && a[pos].first <= i) pq.push(a[pos++]);
        while (!pq.empty()) {
            auto [L, R] = pq.top();
            if (R < i) pq.pop();
            else { ans[i] = (i - L + 1) / 2; break; }
        }
    }

    while (q--) {
        int k;
        cin >> k;

        cout << ans[k] << " ";
    }
}
