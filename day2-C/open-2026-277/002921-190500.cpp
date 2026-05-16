//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define int long long
#define ld long double
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define coutp cout << "       "
#define cont continue
#define F first
#define S second

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
istream& operator>> (istream& in, pair<T, T>& a) {
    in >> a.F >> a.S;
    return in;
}

template<typename T>
ostream& operator<< (ostream& os, pair<T, T>& a) {
    os << a.F << " " << a.S;
    return os;
}

template<typename T>
istream& operator>> (istream& in, vector<T>& a) {
    for (auto& x : a) {
        in >> x;
    }
    return in;
}

template<typename T>
ostream& operator<< (ostream& os, vector<T>& a) {
    for (auto& x : a) {
        os << x << " ";
    }
    return os;
}

constexpr int inf = 2e18, mod = 998244353;
constexpr ld eps = 1e-9;

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int multitest = 1; //cin >> multitest;
    while (multitest--) {
        int n, q; cin >> n >> q;
        vector<pair<int, int>> a(n); cin >> a;
        for (int i = 0; i < q; i++) {
            int x; cin >> x; x--;
            cout << x / 2 << '\n';
        }
    }
    return 0;
}

/*

*/
