#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Point {
    int x, type, right;
};

bool cmp(Point p1, Point p2) {
    return p1.x < p2.x;
}

struct Fenwick {
    vector<int> tree;
    int n;

    Fenwick(int _n) {
        n = _n;
        tree.assign(n + 1, 0);
    }

    void add(int id, int val) {
        for (; id <= n; id += id & -id) {
            tree[id] += val;
        }
    }

    int sum(int r) {
        int res = 0;
        for (; r > 0; r -= r & -r) {
            res += tree[r];
        }
        return res;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<Point> points;
    set<int> st;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        st.insert(l);
        st.insert(r);
        points.push_back({l, 1, r});
        points.push_back({r, -1, r});
    }
    map<int, int> mp;
    int cur = 1;
    for (int s: st) {
        mp[s] = cur++;
    }
    for (int i = 0; i < points.size(); i++) {
        points[i].x = mp[points[i].x];
        points[i].right = mp[points[i].right];
    }
    sort(points.begin(), points.end(), cmp);
    while (q--) {
        int k;
        cin >> k;
        cout << k / 2 << '\n';
    }
    return 0;
    int left = n;
    vector<vector<int>> odd_add(n + 10);
    vector<vector<int>> odd_del(n + 10);
    vector<vector<int>> even_add(n + 10);
    vector<vector<int>> even_del(n + 10);
    Fenwick fenwick(cur + 10);
    for (auto [x, type, right]: points) {
        if (type == 1) {
            left--;
            fenwick.add(right, 1);
            int l1 = n - left;
            int l2 = left;
            int col = fenwick.sum(x + 1, cur);
            int how_much = min(l1 - col, l2);
            if (col % 2 == 0) {
                even_add[col].push_back(col);
                even_del[col + (how_much + 1) * 2].push_back(col);
            } else {
                odd_add[col].push_back(col);
                odd_del[col + (how_much + 1) * 2].push_back(col);
            }
        } else {
            fenwick.add(right, -1);
        }
    }
    multiset<int> even_mt;
    multiset<int> odd_mt;
    vector<int> res(n + 1);
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            for (int id: even_add[i]) {
                even_mt.insert(id);
            }
            for (int id: even_del[i]) {
                even_mt.insert(id);
            }
            res[i] = (i - *(--even_mt.upper_bound(i))) / 2;
        } else {
            for (int id: odd_add[i]) {
                odd_mt.insert(id);
            }
            for (int id: odd_del[i]) {
                odd_mt.insert(id);
            }
            res[i] = (i - *(--odd_mt.upper_bound(i))) / 2;
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << res[k] << ' ';
    }
    return 0;
}