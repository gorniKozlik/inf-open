#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <bitset>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <ext/pb_ds/assoc_container.hpp>

#define iset(t) __gnu_pbds::tree<t, __gnu_pbds::null_type, less<t>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>

#define V vector
#define P pair
#define F first
#define S second

#ifdef LOC
#define $(x) x
#define clog(x) clog << x
#else
#define $(x)
#define clog(x)
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<int> ci;
typedef complex<ll> cll;
typedef complex<ld> cld;
typedef P<int, int> pi;
typedef P<ll, ll> pll;
typedef V<bool> vb;
typedef V<int> vi;
typedef V<ll> vll;

bool scomp(pi x, pi y) {
    return x.S < y.S || (x.S == y.S && x.F < y.F);
}

int n, q;
V<pi> s;
vi k;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    #ifdef STR
    freopen("ti.txt", "r", stdin);
    freopen("tm.txt", "o", stdout);
    #endif

    cin >> n >> q;

    s.resize(n);
    for (auto &x : s) cin >> x.F >> x.S;

    k.resize(q);
    for (auto &x : k) cin >> x;

    vi c;
    for (auto x : s) {
        c.push_back(x.F);
        c.push_back(x.S);
    }

    sort(c.begin(), c.end());

    map<int, int> pr;
    for (auto x : c) {
        pr[x] = pr.size();
    }

    for (auto &x : s) {
        x.F = pr[x.F];
        x.S = pr[x.S];
    }

    // for (auto x : s) {
    //     clog(x.F << " " << x.S << endl);
    // }

    vi diff(2*n + 1, 0);
    for (auto x : s) {
        diff[x.F]++;
        diff[x.S + 1]--;
    }

    vi def(2*n);
    def[0] = diff[0];
    for (int i = 1; i < 2*n; i++) def[i] = def[i-1] + diff[i];

    vi lt, rt;
    for (auto x : s) {
        lt.push_back(x.F);
        rt.push_back(x.S);
    }

    sort(lt.begin(), lt.end());
    sort(rt.begin(), rt.end());

    // for (auto x : rt) clog(x << " ");
    // clog(endl);
    // for (auto x : lt) clog(x << " ");
    // clog(endl);

    vi delta(2*n);
    for (int i = 0; i < 2*n; i++) {
        int rq = lower_bound(rt.begin(), rt.end(), i) - rt.begin();
        int lq = n - (upper_bound(lt.begin(), lt.end(), i) - lt.begin());
        clog(rq << " " << lq << endl);
        delta[i] = min(rq, lq) * 2 + 1;
    }

    for (auto x : def) clog(x << " ");
    clog(endl);
    for (auto x : delta) clog(x << " ");
    clog(endl);

    V<pi> mx(2*n);
    for (int i = 0; i < 2*n; i++) mx[i] = {def[i] + delta[i], def[i]};

    sort(mx.rbegin(), mx.rend());

    V<pi> queries;
    for (int i = 0; i < q; i++) queries.push_back({k[i], i});
    sort(queries.rbegin(), queries.rend());

    // clog(1 << endl);

    vi ans(q, -1);

    int ptr = 0;
    multiset<int> st;
    for (auto x : queries) {
        while (ptr < 2*n && mx[ptr].F >= x.F) {
            st.insert(-mx[ptr].S);
            ptr++;
        }

        auto y = st.begin();
        if (x.F < -*y) ans[x.S] = 0;
        else ans[x.S] = max(0, (x.F + *y) / 2 + (x.F + *y) % 2);
    }

    for (auto x : ans) cout << x << " ";
    cout << "\n";

    return 0;
}