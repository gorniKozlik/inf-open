#include <bits/stdc++.h>

#define all(v) v.begin(), v.end()
#define len(v) (int)v.size()

using namespace std;
using ll = long long;
using ld = long double;

const int INF = 2e9;

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
    vector<int> ans(n + 1, INF);
    for (int k = 1; k <= n; ++k)
    {
        for (int i = k; i + k <= 2 * n; ++i)
        {
            int rt = 0;
            for (auto &pr : a)
            {
                if (pr.first < i && pr.second >= i)
                {
                    ++rt;
                }
            }
            rt = min(rt, k);
            ans[k] = min(ans[k], (k - rt + 1) / 2);
        }
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
