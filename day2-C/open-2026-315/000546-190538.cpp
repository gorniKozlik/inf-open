#include <bits/stdc++.h>

#ifndef LOCAL
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#endif

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

using namespace std;
using ull = unsigned long long;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;

const int mod = 998244353;

struct mint
{
    int x;

    mint(int x = 0) : x(x) {}

    friend mint operator+(mint a, mint b)
    {
        int res = a.x + b.x;
        return res - (res >= mod ? mod : 0);
    }

    friend mint operator-(mint a, mint b)
    {
        int res = a.x - b.x;
        return res + (res < 0 ? mod : 0);
    }

    friend mint operator*(mint a, mint b)
    {
        return ll(a.x) * b.x % mod;
    }
};

mint mpow(mint a, ll b)
{
    mint res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<pii> vec(n);
    vector<pii> line;
    for (int i = 0; i < n; ++i)
    {
        cin >> vec[i].first >> vec[i].second;
        line.emplace_back(vec[i].first, 1);
        line.emplace_back(vec[i].second, -1);
    }
    sort(all(line));
    int cnt = 0;
    int ptr = 2 * n, ptl = 0;
    vector<pii> sp;
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i].second == 1)
        {
            ++cnt;
            ptr -= 2;
        }
        sp.emplace_back(cnt + min(ptr, ptl) + 1, cnt);
        if (line[i].second == -1)
        {
            --cnt;
            ptl += 2;
        }
    }
    sort(rall(sp));
    vector<int> ans(n);
    int pt = 0;
    int mx = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        while (pt < sp.size() && sp[pt].first >= i + 1)
        {
            mx = max(mx, sp[pt].second);
            ++pt;
        }
        ans[i] = max(0, (i + 1 - mx + 1) / 2);
    }
    for (int i = 0; i < q; ++i)
    {
        int x;
        cin >> x;
        cout << ans[x - 1] << ' ';
    }
    cout << '\n';
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    solve();
}