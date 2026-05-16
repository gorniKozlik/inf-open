#include<bits/stdc++.h>
#pragma GCC optimize("O3")
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>

#define ll long long
#define debug(x) cerr << (#x) <<  " = " << x << "\n";
#define pb push_back
#define pii pair < int, int >
#define pll pair < ll, ll >
#define sz(x) (ll)(x.size())
#define all(x) x.begin(), x.end()

const int N = 5e5 + 5;
const int mod = 998244353;
const ll OO = 1e18;

using namespace std;
//using namespace __gnu_pbds;

//template<typename T>
//using oset = tree <T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
bool umx (T &a, T b) {
    return (a < b ? (a = b, 1) : 0);
}

template<typename T>
bool umn (T &a, T b) {
    return (a > b ? (a = b, 1) : 0);
}

int add (int x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    return x >= 0 ? x : x + mod;
}

int mul (int x, int y) {
    return 1ll * x * y % mod;
}

int power (int x, int y) {
    int res = 1;
    while (y) {
        if (y % 2)
            res = mul(res, x);
        x = mul(x, x);
        y >>= 1;
    }
    return res;
}

mt19937 rnd(42);

int mem[N];
int l[N], r[N];

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < N; ++i) mem[i] = N + 1;
    int n, q;
    cin >> n >> q;
    vector < pii > p;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        p.pb({l[i], 1});
        p.pb({r[i], -1});
    }
    sort(all(p));
    int x = 0, y = 0;
    for (auto [a, b] : p) {

        if (b == -1) {
            int ki = x, cur = 0;
            int li = y - x, ri = n - li - x;
//            cout << a << " " << ki << "\n";

            for (int i = 0; i < min(li, ri); ++i) {
                umn(mem[ki], cur++);
                ki += 2;
            }
            umn(mem[ki], cur);
            if (ri > li) {
                umn(mem[ki + 1], 1 + cur);
            }
        } else {
            int ki = x + 1, cur = 0;
            int li = y - x, ri = n - 1 - li - x;
//            cout << a << " " << ki << "\n";
            swap(li, ri);

            for (int i = 0; i < min(li, ri); ++i) {
                umn(mem[ki], cur++);
                ki += 2;
            }
            umn(mem[ki], cur);
            if (ri > li) {
                umn(mem[ki + 1], 1 + cur);
            }
        }

        x += b;
        if (b == 1) ++y;
    }

    for (int i = N - 2; i >= 0; --i) {
        umn(mem[i], mem[i + 1]);
    }
    for (int i = 0, k; i < q; ++i) {
        cin >> k;
        cout << mem[k] << " ";

    }
}
