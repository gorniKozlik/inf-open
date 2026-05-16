#include <bits/stdc++.h>

using namespace std;

#define f(i, n) for(int i=0;i<n;i++)
#define f1(i, n) for(int i=1;i<n;i++)
#define f2(i, n) for(int i=2;i<n;i++)
#define fr(i, n) for(int i=n-1;i>=0;i--)
#define ll long long
// #define ll __int128_
// #define int long long
#define MOD (ll)998244353
#define vi vector<int>
#define vvi vector<vi>
#define vc vector<char>
#define vll vector<ll>
#define vvll vector<vll>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(v) v.begin(), v.end()

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    vi ls(n), rs(n);
    vi vals;
    f(i, n)
    {
        cin >> ls[i] >> rs[i];
        vals.push_back(ls[i]);
        vals.push_back(rs[i]);
    }

    sort(all(vals));
    map<int, int> rv;
    f(i, vals.size())
        rv[vals[i]] = i;
    f(i, n)
    {
        ls[i] = rv[ls[i]];
        rs[i] = rv[rs[i]];
    }

    vi ks(q);
    vi req(n+1, -1);
    vi res(q);
    f(i, q)
    {
        cin >> ks[i];
        req[ks[i]] = i;
    }

    f(i, n+1)
    {
        if (req[i] != -1)
        {
            res[req[i]] = i / 2;
        }
    }

    f(i, q)
        cout << res[i] << ' ';
    return 0;
}