#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>

#define LOCAL

#ifdef LOCAL
void InputInt(int& n) {
    n = rand();
}

#else
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
void InputInt(int& n) {
    std::cin >> n;
}

#endif

struct Fenwick {
    std::vector<int> tree;

    void Update(int pos) {
        for (; pos < tree.size(); pos = pos | (pos + 1)) {
            ++tree[pos];
        }
    }

    int GetSum(int pos) {
        int sum = 0;
        for (; pos >= 0; pos = ((pos + 1) & pos) - 1) {
            sum += tree[pos];
        }

        return sum;
    }

    Fenwick(int size) : tree(size) {}
};

struct SegmentTree {
    struct Node {
        int start;
        int end;
        int max;
    };

    std::vector<Node> tree;

    void Function(int v) {
        tree[v].max = std::max(tree[v * 2 + 1].max, tree[v * 2 + 2].max);
    }

    int Get(int v, int l, int r) {
        if (tree[v].start >= l and tree[v].end <= r) {
            return tree[v].max;
        }

        if (tree[v].start >= r or tree[v].end <= l) {
            return -1e9;
        }

        return std::max(Get(v * 2 + 1, l, r), Get(v * 2 + 2, l, r));
    }

    void Build(int v, int l, int r, std::vector<int>& array) {
        tree[v].start = l;
        tree[v].end = r;

        if (r - l == 1) {
            tree[v].max = array[l];

            return;
        }

        int m = (l + r) / 2;
        Build(v * 2 + 1, l, m, array);
        Build(v * 2 + 2, m, r, array);

        Function(v);
    } 

    SegmentTree(std::vector<int>& array) : tree(array.size() * 4) {
        Build(0, 0, array.size(), array);
    }
};

void Solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int, int>> vec(n);
    std::vector<int> coord;

    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i].first >> vec[i].second;
        coord.push_back(vec[i].first);
        coord.push_back(vec[i].second);
    }

    std::sort(coord.begin(), coord.end());
    for (int i = 0; i < n; ++i) {
        vec[i].first = std::lower_bound(coord.begin(), coord.end(), vec[i].first) - coord.begin();
        vec[i].second = std::lower_bound(coord.begin(), coord.end(), vec[i].second) - coord.begin();
    }

    std::sort(vec.begin(), vec.end());
    Fenwick tree(n * 2);
    std::vector<int> count(n * 2);
    std::vector<int> cnt(n * 2);
    std::vector<int> one_cnt(n + 1, -1e8), two_cnt(n + 1, -1e8);

    int max_x = 0;

    for (int i = 0; i < n; ++i) {
        tree.Update(vec[i].second);
        count[vec[i].first] = tree.GetSum(n * 2 - 1) - tree.GetSum(vec[i].first - 1);
        cnt[vec[i].first] = std::min((i + 1) - count[vec[i].first], n - i - 1);

        max_x = std::max(max_x, count[vec[i].first]);
        one_cnt[count[vec[i].first] + cnt[vec[i].first] * 2] = std::max(one_cnt[count[vec[i].first] + cnt[vec[i].first]], count[vec[i].first]);
        two_cnt[count[vec[i].first] + cnt[vec[i].first] * 2] = std::max(two_cnt[count[vec[i].first] + cnt[vec[i].first] * 2], count[vec[i].first] + cnt[vec[i].first]);
    }

    SegmentTree tree_two_cnt(one_cnt);
    SegmentTree tree_one_cnt(two_cnt);

    int k;
    for (int i = 0; i < q; ++i) {
        std::cin >> k;

        if (k <= max_x) {
            std::cout << 0 << '\n';
        } else {
            int res = 1e9;
            res = std::min(res, (k - tree_two_cnt.Get(0, k, n + 2) + 1) / 2);
            res = std::min(res, k - tree_one_cnt.Get(0, 0, k));

            std::cout << res << '\n';
        }
    }
}

int main() {
    #ifdef LOCAL 
        std::cout << '\n';
    #else
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
    #endif

    int t = 1;
    // std::cin >> t;

    for (int i = 0; i < t; ++i) {
        Solve();
    }
}