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
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].first >> a[i].second;
    vector<pair<int, int>> sc;
    for (int i =0; i < n; i++) {
        sc.push_back({a[i].first, 0});
        sc.push_back({a[i].second, 1});
    }
    sort(sc.begin(), sc.end());
    int cou = 0;
    for (int i = 0; i < n; i++) {
        if (sc[i].second==1)
            cou++;
    }
    cout << cou;
}
