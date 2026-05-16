#include<bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> val;
    std::vector<std::pair<int, int>> segs(n);
    std::vector<int> cnt(2 * n + 1);
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        segs[i] = {l, r};
        val.push_back(l);
        val.push_back(r);
    }
    std::sort(val.begin(), val.end());
    for (auto& [l, r] : segs) {
        l = std::lower_bound(val.begin(), val.end(), l) - val.begin();
        r = std::lower_bound(val.begin(), val.end(), r) - val.begin();
        ++cnt[l], --cnt[r];
    }
    std::partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    std::vector<std::vector<int>> add(n + 2), del(n + 2);
    for (int i = 0; i < 2 * n; ++i) {
        int l = cnt[i];
        int r = std::min(i + 1, 2 * n - i - 1);
        add[0].push_back(l);
        del[r + 1].push_back(l);
    }
    std::multiset<int> st;
    std::vector<int> ans(n + 1);
    for (int i = 0; i <= n; ++i) {
        for (auto x : add[i]) st.insert(x);
        for (auto x : del[i]) st.extract(x);
        ans[i] = std::max(0, (i - *--st.end() + 1) / 2);
    }
    while (q--) {
        int k;
        std::cin >> k;
        std::cout << ans[k] << ' ';
    }
}