#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

bool comp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

int cnt(set<pair<int, int>> v) {
    vector<pair<int, int>> event;
    for (auto [i, j] : v) {
        event.push_back({i, 1});
        event.push_back({j, -1});
    }
    sort(event.begin(), event.end(), comp);
    int ans = 0;
    int temp = 0;
    for (int i = 0; i < event.size(); i++) {
        temp += event[i].second;
        ans = max(ans, temp);
    }
    return ans;
}

void solve() {
    int n, q;
    cin >> n >> q;
    set<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        v.insert({a, b});
    }
    vector<int> ans(n+1, 0);
    int res = cnt(v);
    int prev = res+1;
    for (int k = 0; k < n; k++) {
        for (auto [i, j] : v) {
            auto it = v.rbegin();
            while ((*it).first < j && it != v.rend()) it++;
            if (it != v.rend()) {
                pair<int, int> p = *it;
                v.insert({j, p.first});
                v.insert({i, p.second});
                v.erase({i, j});
                v.erase(p);
                break;
            }
        }
        res = cnt(v);
        for (int j = prev; j <= res; j++) {
            ans[j] = k+1;
        }
        prev = res+1;
        if (prev == n+1) break;
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
