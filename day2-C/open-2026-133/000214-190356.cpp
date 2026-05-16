#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <vector>

// #pragma GCC optimize("O3, Ofast")
// #pragma GCC target("avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

template<class T>
istream &operator>>(istream &in, vector<T> &a) {
    for (auto &i: a) {
        cin >> i;
    }
    return in;
}

template<class T1, class T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
    cin >> a.first >> a.second;
    return in;
}

template<class T>
ostream &operator<<(ostream &out, vector<T> &a) {
    for (auto &i: a) {
        cout << i << ' ';
    }
    cout << '\n';
    return out;
}

mt19937 rnd(20);

void solve();

template<class T>
using oset = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;

signed main() {
#ifdef LOCAL
    freopen(R"(C:\work\untitled\input.txt)", "r", stdin);
    freopen(R"(C:\work\untitled\output.txt)", "w", stdout);

    auto begin_ = chrono::steady_clock::now();
#else
    cin.tie(0);
    cout.tie(0);
    std::ios_base::sync_with_stdio(0);
#endif
    int t_ = 1;
    // cin >> t_;
    while (t_--) {
        solve();
    }
#ifdef LOCAL
    auto end_ = chrono::steady_clock::now();

    cout << "\n\n===========\n";
    cout << chrono::duration_cast<chrono::milliseconds>(end_ - begin_).count() << " ms";
#endif
}

using ll = long long;
// #define int ll

using pii = pair<int, int>;
using vi = vector<int>;
using vp = vector<pii>;
using vv = vector<vi>;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<array<int, 2> > a(n);
    vi an(n + 1, 2 * n);
    vector<array<int, 2> > events;
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
        events.push_back({a[i][0], -1});
        events.push_back({a[i][1], 1});
    }
    int cnt_closed = 0;
    int cnt_open = 0;
    sort(events.begin(), events.end());
    for (auto [l, t]: events) {
        if (t == -1) {
            cnt_open++;
        }

        int mx = cnt_open + min(cnt_closed, n - cnt_closed - cnt_open) * 2 + (1 - (cnt_closed== n - cnt_closed - cnt_open));
        int cost = min(cnt_closed, n - cnt_closed - cnt_open) + (1 - (cnt_closed== n - cnt_closed - cnt_open));

        an[mx] = min(an[mx], cost);

        if (t == 1) {
            cnt_open--;
            cnt_closed++;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (an[i] == 2 * n) {
            an[i] = 0;
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        an[i] = min(an[i], an[i+1]);
    }
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << an[k] << '\n';
    }
}
