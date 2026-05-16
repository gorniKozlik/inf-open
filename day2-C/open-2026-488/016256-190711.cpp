#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <queue>

using namespace std;
using ll = long long;
using ld = long double;

#define int ll

const int MOD = 998'244'353;
const int SIGNES = 6;
const int INF = 1e9;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (auto &i : a) {
        cin >> i.first >> i.second;
    }
    vector<pair<int, int>> idk;
    for (auto &i : a) {
        idk.emplace_back(i.first, 1);
        idk.emplace_back(i.second, 0);
    }
    sort(idk.begin(), idk.end());
    vector<int> lol;
    for (auto &i : idk) {
        lol.push_back(i.second);
    }
    int m = lol.size();
    vector<int> pref(m);
    for (int i = 0; i < m; i++) {
        pref[i] = (i > 0? pref[i - 1] : 0) + lol[i];
    }
    while (q--) {
        int k;
        cin >> k;
        // k *= 2;
        int ans = k - 1;
        int open = 0;
        for (int i = 0; i < m; i++) {
            if (lol[i] == 1) {
                open++;
            } else {
                open--;
            }
            int minus = (i + 1) - pref[i];
            int pluses = (pref.back() - pref[i]);
            if (open + 2 * min(minus, pluses) >= k) {
                ans = min(ans, max((k - open + 1) / 2, 0ll));
            }
        }
        cout << ans << '\n';
    }
}

signed main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(SIGNES);

    int q = 1;

    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
    #endif

    while (q--) {
        solve();
    }

}