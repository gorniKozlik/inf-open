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
        vector<int> compres;
        vector<pair<int, int>> sc;
        for (auto[x, y] : a) {
            compres.pb(x);
            compres.pb(y);
        }
        sort(all(compres));
        for (auto& x : a) {
            x.F = lower_bound(all(compres), x.F) - compres.begin();
            x.S = lower_bound(all(compres), x.S) - compres.begin();
            sc.pb({x.F, -1});
            sc.pb({x.S, 1});
        }
        sort(all(a), [](pair<int, int> a, pair<int, int> b) {return a.S < b.S;});
        sort(all(sc));
        vector<pair<int, int>> dop(2 * n);
        sort(all(sc));
        int cnt1 = 0, cnt2 = 0;
        for (auto[x, type] : sc) {
            //cout << x << " " << type << endl;
            dop[x] = {cnt1, cnt2};
            if (type == -1) {
                dop[x].S++;
                cnt2++;
            } else {
                cnt2--;
                cnt1++;
            }
        }
        sort(all(dop), [&](pair<int, int> a, pair<int, int> b) {
            if (a.S != b.S) {
                return a.S > b.S;
            }
        });
        while (q--) {
            int x; cin >> x;
            int ans = inf;
            for (int i = 0; i < min(100ll, 2 * n); i++) {
                auto[cnt1, cnt2] = dop[i];
                int x2 = x;
                x -= cnt2;
                x = max(0ll, x);
                int cnt3 = n - cnt1 - cnt2;
                int ans2 = min(min(cnt1, cnt3), x / 2);
                x -= 2 * ans2;
                ans2 += x;
                ans = min(ans, ans2);
                x = x2;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}

/*
6 1
25 30
15 29
7 12
8 14
4 5
16 23
4
*/
