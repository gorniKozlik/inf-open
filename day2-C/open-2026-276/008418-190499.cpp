#include <bits/stdc++.h>

using namespace std;
#define int long long int
#define fr(i, a, b) for(int i = (a); i <= b; i++)
#define rf(i, a, b) for(int i = (a); i >= b; i--)
#define fe(i, a) for(auto& i : a)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define lc(S) ((S<<1)+1)
#define rc(S) ((S<<1)+2)
template<typename T>
using v = vector<T>;
using vi = v<int>;
using vvi = v<vi>;
using ii = pair<int, int>;
using vii = v<ii>;
using vvii = v<vii>;

const int mxa = 4e5+10;
const int INF = 1e9;

struct node{
    int max, sum;
    node() {
        max = sum = 0;
    }
};

v<node> t(4*mxa, node());
int sz;

node merge(node a, node b) {
    node res = node();
    res.max = max(a.max, a.sum+b.max);
    res.sum = a.sum + b.sum;
    return res;
};

void upd(int v, int l, int r, int i, int x) {
    if (l > i || r <= i) return;
    if (r-l == 1) {
        t[v].max += x;
        t[v].sum += x;
        return;
    }
    int m = (l+r)>>1;
    upd(lc(v), l, m, i, x);
    upd(rc(v), m, r, i, x);
    t[v] = merge(t[lc(v)], t[rc(v)]);
}
void upd(int i, int x) {
    upd(0, 0, sz, i, x);
}
int query() {
    return t[0].max;
}

bool comp(ii a, ii b) {
    if (a.first != b.first) return a.first < b.first;
    if (a.second == b.second) return 0;
    if (a.second == 1) return 1;
    return 0;
}

void solve() {
    int n, q; cin >> n >> q;
    sz = 2*n;
    vii a; 
    fr(i, 0, n-1) {
        int l, r; cin >> l >> r;
        a.push_back({l, 1});
        a.push_back({r, -1});
    }
    sort(all(a), comp);
    fr(i, 0, sz-1) {
        upd(i, a[i].second);
    }
    vi ans(n+1, 0);
    int k = 0, op = 0, res = query(), l = 0, r = sz-1;
    fr(i, k, res) ans[i] = op; 
    k = res+1; op++;
    while(res < n) {
        while (l < sz && a[l].second != -1) l++;
        while (r > 0 && a[r].second != 1) r--;
        upd(l, +2); l++;
        upd(r, -2); r--;
        res = query();
        fr(i, k, res) ans[i] = op;
        k = res+1; op++;
    }
    fr(i, 0, q-1) {
        int x; cin >> x;
        cout << ans[x] << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t = 1; 
    // cin >> t;
    while (t--) solve();
}