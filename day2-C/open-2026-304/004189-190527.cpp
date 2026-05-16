#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAX = (2e5) + 5;

int n, q;

struct Cell
{
    int l, r;
} a[MAX];

void Solve()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].l >> a[i].r;
    }
    int k;
    for (int i = 0; i < q; i++)
    {
        cin >> k;
        cout << k / 2 << " ";
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