#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#define ll long long
#define X first
#define Y second
#define endl '\n'
using namespace std;

void speed()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}
int n, q;
const int MAXN = 200100;
int k[MAXN];
struct n1
{
    int l, r;
    bool operator<(const n1 &x) const
    {
        if (l != x.l)
            return l < x.l;
        return r < x.r;
    }
};
struct n2
{
    int l, r;
    bool operator<(const n2 &x) const
    {
        if (r != x.r)
            return r < x.r;
        return l < x.l;
    }
};
set<n1> s;
set<n2> rs;
void read()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        s.insert({l, r});
        rs.insert({r, l});
    }
    for (int i = 1; i <= q; i++)
    {
        cin >> k[i];
    }
}
signed main()
{
    speed();
    read();
    int ans = 0;
    while (s.size()>1)
    {
        n1 c1 = *s.begin();
        s.erase(s.begin());
        n2 c2;
        {
            auto it = rs.end();
            it--;
            c2 = *it;
            rs.erase(it);
        }
        s.erase({c2.l,c2.r});
        rs.erase({c1.l,c2.r});
        if (c1.l == c2.l && c1.r == c2.r)
            continue;
        if (c1.r < c2.l)
        {
            ans++;
            s.insert({c1.r, c2.l});
            rs.insert({c1.r, c2.l});
        }
        else
        {
            s.insert({c1.r, c2.l});
            rs.insert({c1.r, c2.l});
        }
    }
    cout<<ans<<endl;
    return 0;
}