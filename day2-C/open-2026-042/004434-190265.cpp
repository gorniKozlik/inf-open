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

#define pII pair<Interval, Interval>

struct Interval {
    int l, r;

    pII middle() const {
        int m = (l + r) / 2;
        return {{l, m}, {m, r}};
    }
};

vector<int> tree, addx;

void apply(int j, int v) {
    tree[j] += v;
    addx[j] += v;
}

void push(int j) {
    apply(2 * j + 1, addx[j]);
    apply(2 * j + 2, addx[j]);
    addx[j] = 0;
}

void mass_update(int j, Interval i, Interval si, int v) {
    if (si.l >= si.r) return;

    if (i.l == si.l & i.r == si.r) {
        apply(j, v);
        return;
    }
    push(j);

    pII mid = i.middle();
    pII sis = {
        {si.l, min(si.r, mid.first.r)},
        {max(si.l, mid.second.l), si.r},
    };

    mass_update(2 * j + 1, mid.first, sis.first, v);
    mass_update(2 * j + 2, mid.second, sis.second, v);

    tree[j] = max(tree[2 * j + 1], tree[2 * j + 2]);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

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

    tree.resize(4 * m);
    addx.resize(4 * m);

    for (int i = 0; i < n; ++i) {
        a[i].l = lower_bound(xs.begin(), xs.end(), a[i].l) - xs.begin();
        a[i].r = lower_bound(xs.begin(), xs.end(), a[i].r) - xs.begin();

        mass_update(0, {0, m}, {a[i].l, a[i].r + 1}, 1);
    }

    set<pair<int, int>> sxl, sxr;
    for (int i = 0; i < n; ++i) {
        sxl.insert({a[i].l, i});
        sxr.insert({a[i].r, i});
    }

    vector<int> timer;
    for (int ix = 0; ; ++ix) {
        timer.push_back(tree[0]);

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
            mass_update(0, {0, m}, {a[j].r, a[i].l + 1}, 2);

            swap(a[i].r, a[j].r);
            swap(a[j].l, a[j].r);
            break;
        }
    }

    for (int _ = 0; _ < q; ++_) {
        int v;
        cin >> v;
        int res = lower_bound(timer.begin(), timer.end(), v) - timer.begin();
        cout << res << " ";
    }
}