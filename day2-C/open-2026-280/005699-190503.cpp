#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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

struct Point {
    int x, type, right;
};

bool cmp(Point p1, Point p2) {
    return p1.x < p2.x;
}

void solve1(int n, int q, vector<pair<int, int>> sc) {
    set<int> st;
    for (int i = 0; i < sc.size(); i++) {
        st.insert(sc[i].first);
        st.insert(sc[i].second);
    }
    map<int, int> mp;
    int cur = 1;
    for (int s: st) {
        mp[s] = cur++;
    }
    vector<Point> points;
    for (int i = 0; i < sc.size(); i++) {
        sc[i].first = mp[sc[i].first];
        sc[i].second = mp[sc[i].second];
        points.push_back({sc[i].first, 1, sc[i].second});
        points.push_back({sc[i].second, -1, sc[i].second});
    }
    sort(points.begin(), points.end(), cmp);
    vector<int> res(n + 1);
    for (int i = 1; i <= n; i++) {
        res[i] = i / 2;
    }
    multiset<int> mt;
    mt.insert(INT_MAX);
    vector<vector<int>> even_add(n + 10);
    vector<vector<int>> even_del(n + 10);
    vector<vector<int>> odd_add(n + 10);
    vector<vector<int>> odd_del(n + 10);
    Fenwick fenwick(cur + 10);
    int cnt = 0;
    for (auto [x, type, right]: points) {
        if (type == 1) {
            cnt++;
            fenwick.add(right, 1);
        }
        int m = fenwick.sum(x + 1, cur + 1);
        int col1 = cnt - m;
        int col2 = n - cnt;
        int col = min(col1, col2);
        if (m % 2 == 0) {
            even_add[m].push_back(m);
            even_del[m + (col + 1) * 2].push_back(m);
        } else {
            odd_add[m].push_back(m);
            odd_del[m + (col + 1) * 2].push_back(m);
        }
    }
    multiset<int> even_mt;
    multiset<int> odd_mt;
    for (int i = 0; i <= n; i++) {
        if (i % 2 == 0) {
            for (int id: even_add[i]) {
                even_mt.insert(id);
            }
            for (int id: even_del[i]) {
                even_mt.erase(even_mt.find(id));
            }
            auto it = even_mt.upper_bound(i);
            if (it != even_mt.begin()) {
                --it;
                res[i] = min(res[i], (i - *it) / 2);
            }
        } else {
            for (int id: odd_add[i]) {
                odd_mt.insert(id);
            }
            for (int id: odd_del[i]) {
                odd_mt.erase(odd_mt.find(id));
            }
            auto it = odd_mt.upper_bound(i);
            if (it != odd_mt.begin()) {
                --it;
                res[i] = min(res[i], (i - *it) / 2);
            }
        }
    }
    while (q--){
        int k;
        cin >> k;
        cout << res[k] << ' ';
    }
}

int solve2(int n, int q, vector<pair<int, int>> sc) {
    vector<int> sorted_arr;
    for (int i = 0; i < n; i++) {
        sorted_arr.push_back(sc[i].first);
        sorted_arr.push_back(sc[i].second);
    }
    sort(sorted_arr.begin(), sorted_arr.end());
    int col = 0;
    auto get_id = [&](int val) {
        return lower_bound(sorted_arr.begin(), sorted_arr.end(), val) - sorted_arr.begin() + 1;
    };
    for (auto [l, r]: sc) {
        if (get_id(l) <= n && get_id(r) > n) {
            col++;
        }
    }
    return (n - col) / 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> sc(n);
    for (int i = 0; i < n; i++) {
        cin >> sc[i].first >> sc[i].second;
    }
    solve1(n, q, sc);
    return 0;
}
/*
4 1
1 3
2 4
0 7
5 6
4
2 1
 */