#include "bits/extc++.h"
//#pragma optimize("O3")
//#pragma target("avx2,popcnt")
//#pragma target("unroll-loops")
using namespace std;
using namespace __gnu_pbds;
using ll = long long;

using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
istream &operator>>(istream &is, vector<T> &a) {
    for (auto &v: a) is >> v;
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, vector<T> &a) {
    for (auto &v: a) os << v << " ";
    return (os << "\n");
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#endif

    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> a(n);
    vector<int> comp;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        comp.push_back(a[i].first);
        comp.push_back(a[i].second);
    }
    std::sort(comp.begin(), comp.end());
    comp.erase(std::unique(comp.begin(), comp.end()), comp.end());
    for (int i = 0; i < n; ++i) {
        a[i].first = lower_bound(comp.begin(), comp.end(), a[i].first) - comp.begin();
        a[i].second = lower_bound(comp.begin(), comp.end(), a[i].second) - comp.begin();
    }

    vector<ll> ans0(n + 2, 1e9);
    vector<vector<pair<int, int>>> ans2(n + 2);
    vector<ll> ans3(n + 2, 1e9);

    vector<ll> ans(n+2, 1e9);
    for (int i = 0; i < 2 * n; ++i) {
        int cnton = 0;
        int cnttouch = 0;
        int cntl = 0;
        int cntr = 0;
        for (int j = 0; j < n; ++j) {
            if (a[j].second < i) cntl++;
            else if (a[j].first > i) cntr++;
            else if (a[j].first == i || a[j].second == i) cnttouch++;
            else cnton++;
        }

        ans0[cnton + cnttouch] = 0;
        ans2[cnton + cnttouch].push_back({cnton + cnttouch, i});

        int can = min(cntl, cntr);

        ans2[cnton + cnttouch + can * 2 + 1].push_back({cnton + cnttouch, i});


        cntl -= can;
        cntr -= can;

        ans3[cnton + cnttouch + can * 2] = can;
    }

    for (int i = n - 2; i >= 0; --i) {
        ans0[i] = min(ans0[i], ans0[i + 1]);
    }

    set<pair<int, int>> can;
    int add = 0;

    for (ll i = 0; i <= n; ++i) {
        for (auto pr: ans2[i]) {
            if (can.contains(pr)) can.erase(pr);
            else can.insert(pr);
        }
        if (can.empty()) continue;
        else {
            ll stt = can.rbegin()->first;
            ans[i] = min(ans[i], (i - stt + 1) / 2);
        }
    }

    for (int i = 1; i <= n; ++i) {
        ans3[i] = min(ans3[i], ans3[i - 1] + 1);
    }
    for (int i = 0; i <= n; ++i) {
        ans[i] = min(ans[i], ans0[i]);
        ans[i] = min(ans[i], ans3[i]);
    }

    while (q--){
        int v;
        cin >> v;

        cout << ans[v] << "\n";
    }
//    cout << ans << "\n";
}