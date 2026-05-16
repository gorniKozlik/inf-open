#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits>
#include <set>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

const int INF = 1e9 + 7;
const ll LL_INF = 4e18;

struct Query {
    int k;
    int ind;
};

const int LEFT = 1, RIGHT = -1;

struct Point {
    int x;
    int type;
};

vector<Point> arr;
vector<Query> qs;

int max_cover() {
    int ans = 0;
    int cur = 0;
    for (const auto& [x, type] : arr) {
        cur += type;
        ans = max(ans, cur);
    }

    return ans;
}

struct SegmentTree {
    int n;
    struct Node {
        ll max;
        ll add;
    };
    vector<Node> tree;

    SegmentTree(const int n)
        : n(n)
    {
        tree.resize(4 * n);
    }

    Node merge(const Node& lhs, const Node& rhs) {
        Node ans;
        assert(lhs.add == 0 && rhs.add == 0);
        ans.add = 0;
        ans.max = max(lhs.max, rhs.max);
        return ans;
    }

    void push(int pos, int left, int right) {
        if (tree[pos].add == 0) return;
        if (right - left != 1) {
            ll add = tree[pos].add;
            tree[2 * pos + 1].add += add;
            tree[2 * pos + 1].max += add;

            tree[2 * pos + 2].add += add;
            tree[2 * pos + 2].max += add;
        }
        tree[pos].add = 0;
    }

    void build(int pos, int left, int right, const vector<ll>& pref) {
        if (right - left == 1) {
            tree[pos].add = 0;
            tree[pos].max = pref[left];
        } else {
            int mid = (left + right) / 2;
            build(2 * pos + 1, left, mid, pref);
            build(2 * pos + 2, mid, right, pref);
            tree[pos] = merge(tree[2 * pos + 1], tree[2 * pos + 2]);
        }
    }

    void build(const vector<ll>& pref) {
        build(0, 0, n, pref);
    }

    void add(int lb, int rb, ll val, int pos, int left, int right) {
        push(pos, left, right);
        if (left >= rb || lb >= right) return;
        if (lb <= left && right <= rb) {
            tree[pos].add += val;
            tree[pos].max += val;
            push(pos, left, right);
        } else {
            int mid = (left + right) / 2;
            add(lb, rb, val, 2 * pos + 1, left, mid);
            add(lb, rb, val, 2 * pos + 2, mid, right);
            tree[pos] = merge(tree[2 * pos + 1], tree[2 * pos + 2]);
        }
    }

    void add(int lb, int rb, ll val) {
        add(lb, rb, val, 0, 0, n);
    }

    Node RMQ(int lb, int rb, int pos, int left, int right) {
        push(pos, left, right);
        if (left >= rb || lb >= right) return Node{-LL_INF, 0};
        if (lb <= left && right <= rb) return tree[pos];
        else {
            int mid = (left + right) / 2;
            Node lc = RMQ(lb, rb, 2 * pos + 1, left, mid);
            Node rc = RMQ(lb, rb, 2 * pos + 2, mid, right);
            return merge(lc, rc);
        }
    }

    ll RMQ(int lb, int rb) {
        return RMQ(lb, rb, 0, 0, n).max;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n, nQ;
    cin >> n >> nQ;


    int lb, rb;
    for (int i = 0; i < n; ++i) {
        cin >> lb >> rb;
        arr.push_back(Point{lb, LEFT});
        arr.push_back(Point{rb, RIGHT});
    }

    for (int q = 0; q < nQ; ++q) {
        int k;
        cin >> k;
        qs.push_back(Query{k, q});
    }

    sort(qs.begin(), qs.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.k < rhs.k;
    });

    sort(arr.begin(), arr.end(), [](const auto& lhs, const auto& rhs) {
       if (lhs.x != rhs.x) return lhs.x < rhs.x;
        return lhs.type > rhs.type;
    });

    multiset<pair<int, int>> lx, rx; // x, ind;
    SegmentTree pref_sgtr(2 * n);
    vector<ll> pref(2 * n);
    pref[0] = arr[0].type;
    for (int i = 0; i < 2 * n; ++i) {
        if (i != 0) pref[i] = pref[i - 1] + arr[i].type;
        if (arr[i].type == LEFT) lx.insert({arr[i].x, i});
        if (arr[i].type == RIGHT) rx.insert({arr[i].x, i});
    }
    pref_sgtr.build(pref);

    vector<int> ans(nQ, INF);
    int cur_ops = 0;
    assert(arr.size() == 2 * n);

    while (true) {
        int mx_c = pref_sgtr.RMQ(0, 2 * n);
        assert(cur_ops <= 2 * n);

        // cout << "AFTER " << cur_ops << ' ' << mx_c << '\n';
        for (int q = 0; q < nQ; ++q) {
            if (qs[q].k <= mx_c) ans[qs[q].ind] = min(ans[qs[q].ind], cur_ops);
        }

        pair<int, int> lmr = *rx.begin();
        pair<int, int> rml = *lx.rbegin();

        if (rml.first <= lmr.first) break;

        pref_sgtr.add(lmr.second, 2 * n, 2);
        pref_sgtr.add(rml.second, 2 * n, -2);
        cur_ops++;
        rx.extract(lmr);
        lx.extract(rml);
        rx.insert(rml);
        lx.insert(lmr);
    }

    for (int i = 0; i < nQ; ++i) cout << ans[i] << ' ';

    return 0;
}