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
    vector<int> mx_inter(n + 1);
    int left = 0;
    int bal = 0;
    for (auto [x, t] : events)
    {
        if (t == -1)
        {
            ++bal;
            int right = n - bal - left;
            int mx_ans = bal;
            if (left > right)
                mx_ans += 2 * right + 1;
            else
                mx_ans += 2 * left;
            mx_inter[mx_ans] = max(mx_inter[mx_ans], bal);
        }
        else
        {
            int right = n - bal - left;
            int mx_ans = bal;
            if (right > left)
                mx_ans += 2 * left + 1;
            else
                mx_ans += 2 * right;
            mx_inter[mx_ans] = max(mx_inter[mx_ans], bal);
            --bal;
            ++left;
        }
    }

    vector<int> query(n + 1, -1);
    for (int i = 0; i < q; i++)
    {
        int k;
        cin >> k;
        query[k] = i;
    }

    vector<int> ans(q);
    int c = 0;
    for (int i = n; i >= 0; i--)
    {
        c = max(c, mx_inter[i]);
        int j = query[i];
        if (j != -1)
            ans[j] = max(i - c + 1, 0) / 2; 
    }

    for (int x : ans)
        cout << x << ' ';
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
