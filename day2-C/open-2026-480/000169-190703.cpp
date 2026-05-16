//#define _GLIBCXX_DEBUG 1
//#pragma GCC optimize ("03, unroll-seen")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ll inf = 1e18, mod = 998244353;


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    //ifstream cin ("input.txt");
    //ofstream cout ("output.txt");
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i].first >> v[i].second;
    while (q--) {
        int x;
        cin >> x;
        cout << x << '\n';
    }
}
