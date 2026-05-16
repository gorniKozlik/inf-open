#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <stack>
#include <random>
#include <ctime>
#include <iomanip>
#include <immintrin.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#define pb push_back
#define eb emplace_back
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
using ld = long double;
mt19937 rnd(234672);
struct ST {
    int n;
    vector<int>t;
    ST() {
        n = 0;
    }
    ST (int _n) {
        n = _n;
        t.assign(n * 4, 0);
    }
    ST resize(int _n) {
        n = _n;
        t.assign(n * 4, 0);
        return 0;
    }
    void build(int i, int l, int r, vector<int>& a) {
        if (r >= l) return;
        if (l + 1 == r) {
            t[i] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * i + 1, l, m, a);
        build(2 * i + 2, m, r, a);
        t[i] = max(t[2 * i + 1], t[2 * i + 2]);
    }
    void build(vector<int>& a) {
        return build(0, 0, n, a);
    }
    int query(int i, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return -1;
        if (ql <= l && r <= qr) {
            return t[i];
        }
        int m = (l + r) / 2;
        return max(query(2 * i + 1, l, m, ql, qr), query(2 * i + 2, m, r, ql, qr));
    }
    int query(int l, int r) {
        return query(0, 0, n, l, r);
    }
    void upd(int i, int l, int r, int qi, int x) {
        if (qi < l || qi >= r) return;
        if (l + 1 == r) {
            t[i] = x;
            return;
        }
        int m = (l + r) / 2;
        upd(2 * i + 1, l, m, qi, x);
        upd(2 * i + 2, m, r, qi, x);
        t[i] = max(t[2 * i + 1], t[2 * i + 2]);
    }
    void upd(int i, int x) {
        return upd(0, 0, n, i, x);
    }
};
struct Sparse {
    int n;
    vector<int>t;
    vector<int>l2;
    vector<vector<int>>d;
    Sparse () {
        n = 0;
    }
    Sparse(int _n) {
        n = _n;
        t.resize(n, 0);
        l2.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            l2[i] = l2[i / 2] + 1;
        }
    }
    void resize(int _n) {
        n = _n;
        t.resize(n, 0);
        l2.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            l2[i] = l2[i / 2] + 1;
        }
    }
    Sparse(vector<int> a) {
        n = a.size();
        t = a;
        l2.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            l2[i] = l2[i / 2] + 1;
        }
        d.assign(n, vector<int>(l2[n] + 1));
        for (int i = 0; i < n; ++i) {
            d[i][0] = t[i];
        }
        for (int j = 1; j <= l2[n]; ++j) {
            for (int i = 0; i < n; ++i) {
                if (i + (1 << j) <= n) {
                    d[i][j] = max(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
                }
            }
        }
    }
    void create(vector<int> a) {
        n = a.size();
        t = a;
        l2.resize(n + 1);
        for (int i = 2; i <= n; ++i) {
            l2[i] = l2[i / 2] + 1;
        }
        d.assign(n, vector<int>(l2[n] + 1));
        for (int i = 0; i < n; ++i) {
            d[i][0] = t[i];
        }
        for (int j = 1; j <= l2[n]; ++j) {
            for (int i = 0; i < n; ++i) {
                if (i + (1 << j) <= n) {
                    d[i][j] = max(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
                }
            }
        }
    }
    void build() {
        for (int i = 2; i <= n; ++i) {
            l2[i] = l2[i / 2] + 1;
        }
        for (int i = 0; i < n; ++i) {
            d[i][0] = t[i];
        }
        for (int j = 1; j <= l2[n]; ++j) {
            for (int i = 0; i < n; ++i) {
                if (i + (1 << j) <= n) {
                    d[i][j] = max(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
                }
            }
        }
    }
    int query(int l, int r) {
        int k = l2[r - l];
        return max(d[l][k], d[r - (1 << k)][k]);
    }
};
struct Fenwik {
    int n;
    vector<int>t;
    Fenwik() {
        n = 0;
    }
    Fenwik(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void add(int i, int x) {
        for (i++; i <= n; i += i & (-i)) {
            t[i] += x;
        }
    }
    int sum(int i) {/// half-intervale[0, i)
        int ans = 0;
        for (; i > 0; i -= i & (-i)) {
            ans += t[i];
        }
        return ans;
    }
    int sum(int l, int r) {/// half-intervale[l, r)
        return sum(r) - sum(l);
    }
};

struct DSU {
    int n;
    vector<int>p;
    bool fuse = true;
    DSU(){n=0;}
    DSU(int _n) {
        n = _n;
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            p[i] = i;
        }
    }
    int get(int i) {
        if (p[i] == i) return i;
        else if (fuse) return p[i] = get(p[i]);
        else return get(p[i]);
    }

    int unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (rnd() % 2) swap(x, y);
        p[x] = y;
        return get(y);
    }
};

const int B = 502;
struct Query {
    int i, l, r, ans;
};
bool operator <(const Query& a, const Query& b) {
    if (a.l / B != b.l / B) return a.l < b.l;
    return a.r < b.r;
}
void solve();
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

const int MAX_N = 100002, MAX_M = 100002;
vector<vector<int>>g;
int vis[MAX_N];
void dfs(int u) {
    cout << u + 1 << ' ';
    vis[u] = 1;
    for (auto v : g[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}
const ll mod = 998244353;
void inverse_1(vector<int>&a) {
    reverse(a.begin(), a.end());
}
void inverse_2(vector<int>&a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        a[i] = a.size() + 1 - a[i];
    }
}
void inverse_3(vector<int>&a) {
    vector<int>b(a.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        b[a[i] - 1] = i + 1;
    }
    a = b;
}
ll binpow(ll a, ll n) {
    if (n == 0) return 1;
    if (n & 1) return a * binpow(a, n - 1) % mod;
    ll x = binpow(a, n >> 1);
    return x * x % mod;
}
ll compute(vector<int>& a) {
    ll sum = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        sum = (sum + binpow(a[i], i + 1)) % mod;
    }
    return sum;
}
ll ans[8];
template<class T1, class foo>
auto unary(foo f, T1 x) {
    return f(x);
}
template<class T1, class T2, class foo>
auto binary(foo f, T1 x, T2 y) {
    return f(x, y);
}
template<class T1, class T2, class T3, class foo>
auto ternary(foo f, T1 x, T2 y, T3 z) {
    return f(x, y, z);
}
int l[200002];
int r[200002];
pair<int, int> a[400002];
int mxp2[400002];
int arr1[400002];
int arr2[400002];
void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        a[2 * i] = {l[i], 1};
        a[2 * i + 1] = {r[i], -1};
    }
    fill(arr1, arr1 + n * 2, -1000000009);
    fill(arr2, arr2 + n * 2, -1000000009);
    int mx = 0, p2 = 0, bal = 0;
    sort(a, a + n * 2);
    int mn2 = 1000000009;
    for (int i = 0; i < n * 2; ++i) {
        bal += a[i].second;
        if (bal > mx) mx = bal;
        if (a[i].second == 1) {
            int p2 = min((i - bal + 1) / 2, (n * 2 - i - bal - 1) / 2);
            arr1[bal + p2 * 2] = max(arr1[bal + p2 * 2], bal + 1);
            //cout << bal + p2 * 2 << ' ' << bal + 1 << "!!!" << endl;
            mxp2[bal] = max(mxp2[bal], p2);
            arr2[bal + p2 * 2 + 1] = max(arr2[bal + p2 * 2 + 1], bal + p2);
            //cout << i - bal + 1 << ' ' << bal << " " << p2 << "!!" << endl;
        }
        //if (bal == mx) {
        ///    p2 = max(p2, min((i - bal + 1) / 2, (n * 2 - i - bal - 1) / 2));
        //}
    }
    for (int i = n * 2 - 2; i >= 0; --i) {
        arr1[i] = max(arr1[i + 1], arr1[i]);
        arr2[i] = max(arr2[i + 1], arr2[i]);
    }
    //cout << mx << ' ' << p2 << endl;
    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        if (k <= mx) {
            cout << 0 << ' ';
            continue;
        }
        int mn = arr2[k];
        //mn = 100002;
        if (arr1[k] != -1000000009) {
            //cout << "{" << arr1[k] << endl;
            mn = min(mn, (k - arr1[k] + 2) / 2);
        }
        cout << mn << ' ';
        ///cout << (k - l + 1) / 2 << '\n';
        /*int ans = n + 1;
        for (int j = 1; j <= n; ++j) {
            ans = min(ans, )
        }*/
    }
    /*int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (r[i] < a[n] || l[i] >= a[n]) {
            cnt++;
        }
    }
    cout << cnt / 2;*/
}

/*

6 10000
5 4 1 3 6 2

3 4
1 2
3 4
5 6
0 1 2 3

*/
