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
    vector<pair<pair<int, int>, int>> sc;
    for (int i =0; i < n; i++) {
        sc.push_back({{a[i].first, 0}, i});
        sc.push_back({{a[i].second, 1}, i});
    }
    sort(sc.begin(), sc.end());
    while (q--) {
        ll x;
        cin >> x;
        ll cou = 0;
        vector<int> v(n);
        ll ls = n*2;
        ll st = 0;
        for (int i = 0; i < x; i++) {
            if (sc[i].first.second==1) {
                cou++;
                st--;
            } else
                st++;
            ls--;
        }
        ll mn = cou;
        for (int i = x; i < n; i++) {
            if (sc[i].first.second==1) {
                st--;
                cou++;
            }else {
                st++;
                cou--;
            }
            mn = min(mn, cou);
        }
        cout << max(mn, 0LL) << ' ';
    }
}
