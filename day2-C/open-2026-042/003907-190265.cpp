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

    bool is_intersect(const Node &that) const {
        return this->l <= that.l && that.l <= this->r || this->l <= that.r && that.r <= this->r;
    }
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

    set<pair<int, int>> sxl, sxr;
    for (int i = 0; i < n; ++i) {
        sxl.insert({a[i].l, i});
        sxr.insert({a[i].r, i});
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

        if (sxl.empty()) {
            break;
        }

        while (!sxl.empty()) {
            int i = sxr.begin()->second;
            int j = (--sxl.end())->second;

            sxr.erase(sxr.begin());
            sxl.erase(--sxl.end());
            if (i == j) continue;
            sxl.erase({a[i].l, i});
            sxr.erase({a[j].r, j});

            if (a[i].is_intersect(a[j]) || a[j].is_intersect(a[i])) continue;

            if (a[j].l <= a[i].r && a[i].r <= a[j].r) continue;
            swap(a[i].r, a[j].r);
            swap(a[j].l, a[j].r);
            break;
        }
    }

    for (int i = 1; i < timer.size(); ++i)
        if (timer[i] - timer[i - 1] != 2) exit(329);

    for (int _ = 0; _ < q; ++_) {
        int v;
        cin >> v;
        int res = lower_bound(timer.begin(), timer.end(), v) - timer.begin();
        cout << res << " ";
    }
}