#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

inline pair<int, int> swp(pair<int, int> x)
{
    return {x.second, x.first};
}

struct node
{
    int mx = 0, mxk, push = 0;
};

inline void pushnode(vector<node>& t, int v, int tl, int tr)
{
    if (t[v].push)
    {
        t[v].mx += t[v].push;
        if (tl != tr)
        {
            t[v << 1].push += t[v].push;
            t[v << 1 | 1].push += t[v].push;
        }
        t[v].push = 0;
    }
}

inline void updnode(vector<node>& t, int v)
{
    if (t[v << 1].mx != t[v << 1 | 1].mx)
    {
        if (t[v << 1].mx > t[v << 1 | 1].mx)
            t[v].mx = t[v << 1].mx, t[v].mxk = t[v << 1].mxk;
        else
            t[v].mx = t[v << 1 | 1].mx, t[v].mxk = t[v << 1 | 1].mxk;
    }
    else
    {
        t[v].mx = t[v << 1].mx;
        t[v].mxk = t[v << 1].mxk + t[v << 1 | 1].mxk;
    }
}

inline void build(vector<node>& t, int v, int tl, int tr)
{
    t[v].mxk = tr - tl + 1;
    if (tl != tr)
    {
        int tm = (tl + tr) >> 1;
        build(t, v << 1, tl, tm);
        build(t, v << 1 | 1, tm + 1, tr);
    }
}

void update(vector<node>& t, int v, int tl, int tr, int l, int r, int x)
{
    pushnode(t, v, tl, tr);
    if (tr < l || r < tl)
        return;
    if (l <= tl && tr <= r)
    {
        t[v].push += x;
        pushnode(t, v, tl, tr);
    }
    else
    {
        int tm = (tl + tr) >> 1;
        update(t, v << 1, tl, tm, l, r, x);
        update(t, v << 1 | 1, tm + 1, tr, l, r, x);
        updnode(t, v);
    }
}

void get(vector<node>& t, int v, int tl, int tr, int l, int r, int& tmx, int& tmxk)
{
    pushnode(t, v, tl, tr);
    if (tr < l || r < tl)
        return;
    if (l <= tl && tr <= r)
    {
        if (t[v].mx > tmx)
            tmx = t[v].mx, tmxk = t[v].mxk;
        else if (t[v].mx == tmx)
            tmxk += t[v].mxk;
    }
    else
    {
        int tm = (tl + tr) >> 1;
        get(t, v << 1, tl, tm, l, r, tmx, tmxk);
        get(t, v << 1 | 1, tm + 1, tr, l, r, tmx, tmxk);
        updnode(t, v);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i].first >> v[i].second;

    set<int> allxs;
    for (int i = 0; i < n; ++i)
        allxs.insert(v[i].first), allxs.insert(v[i].second);
    vector<int> allx(allxs.begin(), allxs.end());
    int e = allx.size();
    for (int i = 0; i < n; ++i)
    {
        v[i].first = lower_bound(allx.begin(), allx.end(), v[i].first) - allx.begin();
        v[i].second = lower_bound(allx.begin(), allx.end(), v[i].second) - allx.begin();
    }
    vector<node> t(e << 2);
    build(t, 1, 0, e - 1);
    for (int i = 0; i < n; ++i)
        update(t, 1, 0, e - 1, v[i].first, v[i].second, 1);

    vector<pair<int, int>> lr, rl;
    for (int i = 0; i < n; ++i)
        lr.push_back({v[i].first, v[i].second}), rl.push_back({v[i].second, v[i].first});
    sort(lr.begin(), lr.end());
    sort(rl.begin(), rl.end());
    vector<bool> lract(n, true), rlact(n, true);

    vector<int> ans(n + 1, n);
    int tk = t[1].mx;
    for (int i = 0; i <= tk; ++i)
        ans[i] = 0;
    int tans = 0;

    int lri = n - 1, rli = 0;
    while (tk != n)
    {
        ++tans;
        while (!lract[lri])
            --lri;
        while (!rlact[rli])
            ++rli;
        pair<int, int> left = swp(rl[rli]), right = lr[lri];
        lract[lri] = false, rlact[rli] = false;
        if (left.second > right.first)
            break;
        int mx1 = -1, mxk1;
        get(t, 1, 0, e - 1, left.first, left.second, mx1, mxk1);
        get(t, 1, 0, e - 1, right.first, right.second, mx1, mxk1);
        int pl = 2;
        if (mx1 == t[1].mx && mxk1 == t[1].mxk)
            --pl;
        for (int i = tk + 1; i <= tk + pl; ++i)
            ans[i] = tans;
        tk += pl;
        update(t, 1, 0, e - 1, left.first, left.second, -1);
        update(t, 1, 0, e - 1, right.first, right.second, -1);
    }

    while (q--)
    {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
    return 0;
}
