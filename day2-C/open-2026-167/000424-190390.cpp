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


    vector<int> ques(q);
    cin >> ques;

    vector<int> ans(q, 1e9);
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

        for (int j = 0; j < q; ++j) {
            int on = cnton;
            int touch = cnttouch;
            int l = cntl;
            int r = cntr;

            if (on >= ques[j]) {
                ans[j] = min(ans[j], 0);
            }
            int need = ques[j] - on - touch;
            int can2 = min(l, r);
            can2 = min(can2, (need+1)/2);

            if (2 * can2 >= need) {
                ans[j] = min(ans[j], can2);
            }

            need -= min(need, can2 * 2);
            l -= can2;
            r -= can2;

            int can1 = min(l + r, touch);
            if (can1 >= need){
                ans[j] = min(ans[j], can2 + need);
            }
        }
    }

    for (int i = q - 2; i >= 0; --i) {
        ans[i] = min(ans[i],ans[i + 1]);
    }

    cout << ans << "\n";
}