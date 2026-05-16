#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;

template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector <pair <int, int>> p(n), p1(n);
    set <pair <int, int>> ps;
    vector <int> ks(q);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
        ps.emplace(p[i].first, 1);
        ps.emplace(p[i].second, -1);
    }
    p1 = p;

    for (int i = 0; i < q; i++) {
        cin >> ks[i];
    }

    sort(p.begin(), p.end(), [](auto i, auto j) {
        return i.first < j.first;
    });

    sort(p1.begin(), p1.end(), [](auto i, auto j) {
        return i.second > j.second;
    });

    vector <int> ans(n+1, 1e9);
    int cntused = 0;

    int cntcur = 0;
    for (auto i : ps) {
        cntcur += i.second;
        ans[cntcur] = min(ans[cntcur], cntused);
    }

    while (!p.empty()) {
        auto vl = p.back();
        auto vr = p1.back();
        p.pop_back();
        p1.pop_back();
        cntused++;

        if (vr.second > vl.first) {
            break;
        }

        ps.erase(ps.find({vr.second, -1}));
        ps.erase(ps.find({vl.first, 1}));
        ps.emplace(vl.first, -1);
        ps.emplace(vr.second, 1);

        int cntcur = 0;
        for (auto i : ps) {
            cntcur += i.second;
            ans[cntcur] = min(ans[cntcur], cntused);
        }
    }

    for (auto i : ks) {
        cout << ans[i] << '\n';
    }
}
