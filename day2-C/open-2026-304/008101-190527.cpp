#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAX = (2e5) + 5;

int n, q, pre[2 * MAX];

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
    for (int i = 0; i < 2 * n; i++)
    {
        pre[i + 1] = pre[i];
        if (v[i].r == 2)
            pre[i + 1]++;
    }
    int k, ans;
    for (int i = 0; i < q; i++)
    {
        cin >> k;
        ans = k;
        for (int j = k; j <= 2 * n - k; j++)
            ans = min(ans, pre[j] - pre[j - k]);
        cout << ans << " ";
    }
    cout << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    Solve();
    return 0;
}