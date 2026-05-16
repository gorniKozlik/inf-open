#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <deque>
#include <queue>
#include <random>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <numeric>
#include <cmath>

using namespace std;
using ll = long long;
using ld = long double;
//333
const int inf = 1e9 + 7;
const ll INF = 4e18;
const ll MOD = 998'244'353;

void solve () {
    int n; cin >> n;
    int q; cin >> q;
    vector<pair<int, int>> a(n);
    vector<int> b(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        b[2 * i] = a[i].first;
        b[2 * i + 1] = a[i].second;
    }
    sort(b.begin(), b.end());
    int m = b[n - 1];
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i].first > m) ans++;
        //if (a[i].second <= m) ans++;
    }
    cout << ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1; //cin >> t;
    while (t--) {
        solve();
    }
}
