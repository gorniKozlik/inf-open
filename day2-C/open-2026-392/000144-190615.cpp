#include <iostream>
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
#define sz(x) (int)(x.size())
#define all(x) x.begin(), x.end()
//#define endl "\n"

template<class T>
istream& operator >> (istream& in, pair<T, T>& a) {
    in >> a.first >> a.second;
    return in;
}
template<class T>
istream& operator >> (istream& in, vector<T>& a) {
    for (T& x : a){
        in >> x;
    }
    return in;
}
template<class T>
ostream& operator << (ostream& out, pair<T, T> a) {
    out << a.first << " " << a.second << " ";
    return out;
}
template<class T>
ostream& operator << (ostream& out, vector<T> a) {
    for (auto& x : a) {
        out << x << " ";
    }
    return out;
}
#define debug(x) cout << (#x) << ": " << (x) << endl

constexpr int inf = 1e9 + 1;
constexpr ll INF = 1e18 + 1;

vi solve3(int n, vi& qq) {
    vi ans(n);
    for (int i = 1; i < n; i++) {
        ans[i] = (i + 1) / 2;
    }
    vi vec;
    for (auto x : qq) {
        vec.push_back(ans[x - 1]);
    }
    return vec;
}

void solve() {
    int n, q; cin >> n >> q;
    vector<pi> segs(n);
    for (int i = 0; i < n; i++) {
        cin >> segs[i].first >> segs[i].second;
    }
    vi qq(q); cin >> qq;
    sort(all(segs));
    bool flag3 = true;
    for (int i = 1; i < n; i++) {
        if (segs[i - 1].second >= segs[i].first) {
            flag3 = false;
        }
    }
    if (flag3) {
        cout << solve3(n, qq) << endl;
        return;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}
