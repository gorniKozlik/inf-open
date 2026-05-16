#pragma GCC optimize("O3,unroll-loops")
#include <vector>
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using dbl = long double;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    int n, q;
    cin >> n >> q;
    map<int, int> mp;
    vector<pair<int, int>> p(n);
    for (auto& [i, j] : p) {
        cin >> i >> j;
        mp[i] = 0;
        mp[j] = 0;
    }
    int x = 0;
    for (auto& [i, j] : mp) j = x++;
    vector<int> ev(2 * n);
    for (auto& [i, j] : p) {
        i = mp[i];
        j = mp[j];
        ev[i]++;
        ev[j]--;
    }

    vector<int> ans(n + 1);
    vector<int> cnt(2 * n - 1, ev[0]);
    for (int i = 1; i < 2 * n; i++) {
        cnt[i] = cnt[i - 1] + ev[i];
    }
    for (int i = 0; i < n; i++) {
        int x = (n - 1) - i;
        int y = (n - 1) + i;
        if (i != 0) ans[n - i] = ans[n - i + 1];
        ans[n - i] = ((n - i) - max(cnt[x], cnt[y]) + 1) / 2;
    }

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        cout << ans[t] << " ";
    }
}