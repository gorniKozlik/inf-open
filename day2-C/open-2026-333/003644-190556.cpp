// # define _GLIBCXX_DEBUG
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
// #pragma GCC optimize("trapv")
#include <bits/extc++.h>

using namespace std;

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

# define int long long
# define all(v) v.begin(),v.end()

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

const int maxn = 2e5 + 10;
int tree[maxn * 4];

void build(int v, int l, int r, const vector<int> &a) {
    if (r - l == 1) {
        if (l < a.size())
            tree[v] = a[l];
    } else {
        int mid = ((r - l) >> 1) + l;
        build(2 * v + 1, l, mid, a);
        build(2 * v + 2, mid, r, a);
        tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    }
}

inline int get(int lx, int rx, int v, int l, int r) {
    if (lx <= l && r <= rx)
        return tree[v];
    if (r <= lx || rx <= l)
        return 0;
    int mid = ((r - l) >> 1) + l;
    return max(get(lx, rx, 2 * v + 1, l, mid), get(lx, rx, 2 * v + 2, mid, r));
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#elif DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int n, q;
    cin >> n >> q;
    vector<pii> seg(n);
    for (auto &elem: seg)
        cin >> elem.first >> elem.second;
    vector<pii> ev;
    for (auto const elem: seg) {
        ev.emplace_back(elem.first, -1);
        ev.emplace_back(elem.second, 1);
    }
    sort(all(ev));
    vector<int> cnt(2 * n - 1);
    int bal = 0;
    int it = 0;
    for (auto const [x, t]: ev) {
        bal -= t;
        if (it != 2 * n - 1)
            cnt[it] = bal;
        ++it;
    }
    build(0, 0, maxn, cnt);
    while (q--) {
        int x;
        cin >> x;
        int l = 0 + (x - 1);
        int r = (2 * n - 1) - x;
        int ost = max(x - get(l, r + 1, 0, 0, maxn), 0ll);
        cout << (ost + 1) / 2 << " ";
    }

    return 0;
}
