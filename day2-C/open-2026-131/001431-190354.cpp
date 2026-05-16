#include "iostream"
#include "vector"
#include "queue"
#include "array"
#include "algorithm"
/*
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
*/
using ll = long long;

const int N = 2e5;

struct SegmentTree{
    std::array<int, 2 * 2 * N> t, push;
    
    void apply(int v, int x){
        t[v] += x;
        push[v] += x;
    }

    void make_push(int v, int l, int m){
        if(push[v] == 0){
            return;
        }
        apply(v + 1, push[v]);
        apply(v + 2 * (m - l), push[v]);
        push[v] = 0;
    }

    void update(int v, int l, int r, int ql, int qr, int x){
        if(qr <= l || r <= ql){
            return;
        }
        if(ql <= l && r <= qr){
            apply(v, x);
            return;
        }
        int m = (r + l) / 2;
        make_push(v, l, m);
        update(v + 1, l, m, ql, qr, x);
        update(v + 2 * (m - l), m, r, ql, qr, x);
        t[v] = std::max(t[v + 1], t[v + 2 * (m - l)]);
    }
};

struct segment{
    int l = 0, r = 0;

    segment() = default;

    segment(int _l, int _r) : l(_l), r(_r) {

    }

    bool operator<(const segment &p) const {
        return l < p.l || (p.l == l && r < p.r);
    }
};

SegmentTree t;

void not_main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<segment> s(n);
    std::vector<int> tmp;
    for(auto &i : s){
        std::cin >> i.l >> i.r;
        tmp.emplace_back(i.l);
        tmp.emplace_back(i.r);
    }
    std::sort(s.begin(), s.end());
    std::sort(tmp.begin(), tmp.end());
    tmp.resize(std::unique(tmp.begin(), tmp.end()) - tmp.begin());
    for(auto &i : s){
        i.l = std::lower_bound(tmp.begin(), tmp.end(), i.l) - tmp.begin();
        i.r = std::lower_bound(tmp.begin(), tmp.end(), i.r) - tmp.begin();
        t.update(1, 0, 2 * n, i.l, i.r + 1, 1);
    }
    std::vector<int> ans(n + 1, -1);
    for (int i = 0, it = 0, cnt = 0; i < n; ++i) {
        for (; it <= t.t[1]; ++it) {
            ans[it] = cnt;
        }
        if (s[n - i - 1].l <= s[i].r) {
            continue;
        }
        ++cnt;
        t.update(1, 0, 2 * n, s[i].r + 1, s[n - i - 1].l, 2);
        t.update(1, 0, 2 * n, s[i].r, s[i].r + 1, 1);
        t.update(1, 0, n, s[n - i - 1].l, s[n - i - 1].l + 1, 1);
    }
    for(int i = 0; i < q; ++i){
        int k;
        std::cin >> k;
        std::cout << ans[k] << ' ';
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int tests = 1;
    // std::cin >> tests;
    while (tests--) {
        not_main();
    }
    return 0;
}
