#include <bits/stdc++.h>

#define all(v) v.begin(), v.end()
#define len(v) (int)v.size()

using namespace std;
using ll = long long;
using ld = long double;

const int INF = 2e9;


struct Seg_treemx
{
    vector<int> tr;
    vector<int> a;
    int n;
    Seg_treemx() {}
    Seg_treemx(vector<int> &_a)
    {
        a = _a;
        n = len(a);
        tr.resize(4 * n);
        build(0, 0, n);
    }
    void build(int v, int l, int r)
    {
        if (r - l == 1)
        {
            tr[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m, r);
        tr[v] = max(tr[2 * v + 1], tr[2 * v + 2]);
    }
    int get(int v, int l, int r, int ql, int qr)
    {
        if (l >= qr || r <= ql) return -INF;
        if (l >= ql && r <= qr) return tr[v];
        int m = (l + r) / 2;
        return max(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<int> xs;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i].first >> a[i].second;
        xs.push_back(a[i].first);
        xs.push_back(a[i].second);
    }
    sort(all(xs));
    vector<int> lt(2 * n);
    for (int i = 0; i < n; ++i)
    {
        a[i].first = lower_bound(all(xs), a[i].first) - xs.begin();
        a[i].second = lower_bound(all(xs), a[i].second) - xs.begin();
        //cout << a[i].first << ' ' << a[i].second << endl;
        lt[a[i].first] = 1;
        lt[a[i].second] = 0;
    }
    vector<int> opn(2 * n), cls(2 * n);
    for (auto &pr : a)
    {
        opn[pr.first]++;
        cls[pr.second]++;
    }
    vector<int> rt(2 * n);
    int cur = 0;
    for (int i = 0; i < 2 * n; ++i)
    {
        rt[i] = cur;
        cur += opn[i];
        cur -= cls[i];
    }
    Seg_treemx tr(rt);
    vector<int> ans(n + 1, INF);
    for (int k = 1; k <= n; ++k)
    {
        ans[k] = (k - min(k, tr.get(0, 0, 2 * n, k, 2 * n - k + 1)) + 1) / 2;
    }
    for (int i = 0; i < q; ++i)
    {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    //cin >> t;

    while (t--)
    {
        solve();
        cout << '\n';
    }
    return 0;
}
