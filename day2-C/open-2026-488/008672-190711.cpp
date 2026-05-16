#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <iomanip>

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
    while (q--) {
        int x;
        cin >> x;
        cout << x / 2 << '\n';
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