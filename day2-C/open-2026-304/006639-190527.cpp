#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAX = (2e5) + 5;

int n, q;

struct Cell
{
    int l, r;
} a[MAX];

bool Cmp(Cell a, Cell b)
{
    if (a.l == b.l)
        return a.r < b.r;
    return a.l < b.l;
}

void Solve()
{
    cin >> n >> q;
    vector<Cell> v;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].l >> a[i].r;
        v.push_back({a[i].l, 1});
        v.push_back({a[i].r, 2});
    }
    sort(v.begin(), v.end(), Cmp);
    int k, ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i].r == 1)
            ans++;
    }
    for (int i = 0; i < q; i++)
    {
        cin >> k;
    }
    cout << ans << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    Solve();
    return 0;
}