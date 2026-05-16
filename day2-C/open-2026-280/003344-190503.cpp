#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> sc(n);
    vector<int> sorted_arr;
    for (int i = 0; i < n; i++) {
        cin >> sc[i].first >> sc[i].second;
        sorted_arr.push_back(sc[i].first);
        sorted_arr.push_back(sc[i].second);
    }
    int col = n;
    auto get_id = [&](int val) {
        return lower_bound(sorted_arr.begin(), sorted_arr.end(), val) - sorted_arr.begin() + 1;
    };
    for (auto [l, r]: sc) {
        if (get_id(l) <= n && get_id(r) > n) {
            col--;
        }
    }
    int k;
    cin >> k;
    cout << (n - k) / 2 << ' ';
    return 0;
    sort(sc.begin(), sc.end());
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
    int r = 0;
    for (int l = 0; l < n; l++) {
        while (r < n && sc[r].first < *mt.begin()) {
            mt.insert(sc[r].second);
            r++;
            int left = l;
            int mid = r - l;
            int right = n - r;
            int col = min(left, right);
            if (mid % 2 == 1) {
                odd_add[mid].push_back(mid);
                odd_del[mid + (col + 1) * 2].push_back(mid);
            } else {
                even_add[mid].push_back(mid);
                even_del[mid + (col + 1) * 2].push_back(mid);
            }
        }
        mt.erase(mt.find(sc[l].second));
    }
    multiset<int> even_mt;
    multiset<int> odd_mt;
    for (int i = 1; i <= n; i++) {
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
    while (q--) {
        int k;
        cin >> k;
        cout << res[k] << ' ';
    }
    return 0;
}