#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cassert>
#include <random>
#define rep(n) for (int (i) = 0; (i) < (n); (i)++)
#define all(n) (n).begin(), (n).end()
#define rall(n) (n).rbegin(), (n).rend()
#define mp make_pair
#define ll long long
#define ld long double
//#define int long long
//#define FILE
//#define DEBUG

using namespace std;

void solve() {
    int n, q; cin >> n >> q;
    vector<pair<int, int>> A(n);
    rep(n) {
        cin >> A[i].first >> A[i].second;
    }
    vector<int> Q(q);
    rep(q) cin >> Q[i];
    vector<int> P;
    rep(n) {
        P.push_back(A[i].first);
        P.push_back(A[i].second);
    }
    sort(all(P));
    int m = P[P.size() / 2];
    int ans = 0;
    rep(n) {
        if (A[i].second < m)
            ans++;
    }
    cout << ans << endl;
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);
#ifdef FILE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "W", stdout);
#endif
#ifndef DEBUG
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
#else

#endif
}