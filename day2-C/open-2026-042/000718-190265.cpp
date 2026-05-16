#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <array>
#include <unordered_set>
#include <unordered_map>

using namespace std;
using ll = long long;
using ld = long double;

struct Node {
    int l, r;
};

signed main() {
    int n, q;
    cin >> n >> q;

    vector<int> xs;
    vector<Node> a(n);

    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        
        xs.push_back(l);
        xs.push_back(r);
        a[i] = {l, r};
    }

    sort(xs.begin(), xs.end());
    xs.resize(unique(xs.begin(), xs.end()) - xs.begin());
    int m = xs.size();

    for (int i = 0; i < n; ++i) {
        a[i].l = lower_bound(xs.begin(), xs.end(), a[i].l) - xs.begin();
        a[i].r = lower_bound(xs.begin(), xs.end(), a[i].r) - xs.begin();
    }

    set<pair<int, int>> sx;
    for (int i = 0; i < n; ++i) {
        sx.insert({a[i].l, i});
        sx.insert({a[i].r, i});
    }

    vector<int> timer;
    for (int ix = 0; ; ++ix) {
        vector<int> scan(m + 1);
        for (auto [l, r] : a) {
            scan[l]++;
            scan[r + 1]--;
        }

        int now = 0, res = 0;
        for (auto el : scan) {
            now += el;
            res = max(res, now);
        }
        timer.push_back(res);

        while (!sx.empty()) {
            int i = sx.begin()->second;
            int j = (--sx.end())->second;

            sx.erase(sx.begin());
            sx.erase(--sx.end());
            if (i == j) continue;
            sx.erase({a[i].r, i});
            sx.erase({a[j].l, j});

            if (a[j].l <= a[i].r && a[i].r <= a[j].r) continue;
            swap(a[i].r, a[j].r);
            swap(a[j].l, a[j].r);
            break;
        }
        if (sx.empty()) break;
    }

    for (int _ = 0; _ < q; ++_) {
        int v;
        cin >> v;
        int res = lower_bound(timer.begin(), timer.end(), v) - timer.begin();
        cout << res << " ";
    }
}