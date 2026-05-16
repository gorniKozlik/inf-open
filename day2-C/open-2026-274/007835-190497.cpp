#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll inf = 1e18;

int n, q;
vector<pair<int, int>> arr;
vector<int> ask;

void parse() {
    cin >> n >> q;
    arr.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i].first >> arr[i].second;
    ask.resize(q);
    for (int i = 0; i < q; ++i)
        cin >> ask[i];
}

void solve() {
    parse();
    for (auto k : ask) {
        cout << k / 2 << " ";
    }
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    solve();
}