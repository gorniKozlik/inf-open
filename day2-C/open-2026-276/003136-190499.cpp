#include <bits/stdc++.h>

using namespace std;
#define int long long int
#define fr(i, a, b) for(int i = (a); i <= b; i++)
#define rf(i, a, b) for(int i = (a); i >= b; i--)
#define fe(i, a) for(auto& i : a)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
template<typename T> 
using v = vector<T>;
using vi = v<int>;
using vvi = v<vi>;
using ii = pair<int, int>;
using vii = v<ii>;
using vvii = v<vii>;

bool comp(ii a, ii b) {
    if (a.second != b.second) return (a.second < b.second);
    return a.first < b.first;
}

void solve() {
    int n, q; cin >> n >> q;
    vii a(n); fe(c, a) cin >> c.first >> c.second;
    // sort(all(a), comp);
    // sort(all(a));
    // fe(c, a) cout << c.first << " " << c.second << '\n';
    fr(i, 0, q-1) {
        int x; cin >> x;
        cout << (x+1)/2 << '\n';
    }
    // set<array<int, 3>> s; fr(i, 0, n-1) s.insert({a[i].first, a[i].second, i});
    // int k = 0;
    // int r = 0;
    // fr(i, 0, n-1) {

    // }

}

signed main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t = 1; 
    // cin >> t;
    while (t--) solve();
}