#include <bits/stdc++.h>

using ll = long long int;
using ull = unsigned long long int;

using namespace std;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

void solve()
{
    int n, q;
    cin >> n >> q;


    vector<pair<int, int>> events; // x, t
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;

        events.emplace_back(l, -1);
        events.emplace_back(r, 1);
    }

    sort(all(events));

    for (int i = 0; i < q; i++)
    {
        int k;
        cin >> k;

        cout << k / 2 << ' ';
    }
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
#ifdef LOCAL
    freopen("C:/work/Day 2/in.txt", "r", stdin);
    freopen("C:/work/Day 2/out.txt", "w", stdout);
    cin >> t;
#endif

    while (t--)
        solve();
    return 0;
}
