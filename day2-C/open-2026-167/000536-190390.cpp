#include "bits/extc++.h"
//#pragma optimize("O3")
//#pragma target("avx2,popcnt")
//#pragma target("unroll-loops")
using namespace std;
using namespace __gnu_pbds;
using ll = long long;

using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
istream & operator>>(istream &is, vector<T> &a){
    for (auto &v: a) is >> v;
    return is;
}

template<typename T>
ostream & operator<<(ostream &os, vector<T> &a){
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
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }

    for (int i = 0; i < q; ++i) {
        int v;
        cin >> v;

        cout << v/2 << "\n";
    }
}