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
    
    vi op(2*n), id(2*n);
    f(i, n)
    {
        ls[i] = rv[ls[i]];
        rs[i] = rv[rs[i]];
        op[ls[i]] = 1;
        id[ls[i]] = i;
        op[rs[i]] = -1;
        id[rs[i]] = i;
    }

    vi cr(2*n);
    int cur = 0;
    int mast = 1;
    f(i, 2*n)
    {
        cur += op[i];
        cr[i] = cur;
        mast = max(mast, cur);
    }

    vi ks(q);
    vi req(n+1, -1);
    vi res(q, 1e9);
    f(i, q)
    {
        cin >> ks[i];
        req[ks[i]] = i;
    }

    f(k, n+1)
    {
        if (req[k] != -1)
        {
            int& r = res[req[k]];
            f(i, 2*n)
            {
                if (cr[i] >= k)
                    r = 0;
                int lr = (i - cr[i] + 1) / 2;
                int rr = (2*n - i - cr[i] - 3) / 2;
                int mr = min(lr, rr);
                int t = 0;
                int v = cr[i];
                while (v < k)
                {
                    if (mr > 0)
                    {
                        mr--;
                        v += 2;
                    }
                    else
                        v++;
                    t++;
                }
                r = min(r, t);
            }


            // if (i <= mast)
            //     r = 0;
            // r = min(r, i / 2);
        }
    }

    f(i, q)
        cout << res[i] << ' ';
    return 0;
}