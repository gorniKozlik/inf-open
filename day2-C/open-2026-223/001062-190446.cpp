#include <bits/stdc++.h>
#define ll long long
#define int ll
#define all(x) x.begin(), x.end()
#define allr(x) x.rbegin(), x.rend()
#define uniq(x) x.erase(unique(all(x)), x.end())
#define fast_cin() cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0)

#pragma optimize("O3")
#pragma target("avx2")
using namespace std;

mt19937 rng(696969);


signed main() {
    fast_cin();
    int n,q; cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (auto &i: a) cin >> i.first >> i.second;
    vector<int> k(q);
    for (int &i: k) cin >> i;
    for (int &i: k) {
        cout << i/2 << ' ';
    }
}