#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

inline pair<int, int> swp(pair<int, int> x)
{
    return {x.second, x.first};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i].first >> v[i].second;
    set<pair<int, int>> lr, rl;
    for (int i = 0; i < n; ++i)
        lr.insert({v[i].first, v[i].second}), rl.insert({v[i].second, v[i].first});
    int mxk = -1, mxx;
    {
        set<pair<int, int>> ev;
        for (int i = 0; i < n; ++i)
            ev.insert({v[i].first, 1}), ev.insert({v[i].second, -1});
        int tk = 0;
        for (pair<int, int> i : ev)
        {
            tk += i.second;
            if (tk > mxk)
                mxk = tk, mxx = i.first;
        }
    }
    vector<int> ans(n + 1, n);
    for (int i = 0; i <= mxk; ++i)
        ans[i] = 0;
    int tk = mxk;
    int tans = 0;
    while (tk != n)
    {
        pair<int, int> left = swp(*rl.begin()), right = *lr.rbegin();
        lr.erase(left), lr.erase(right);
        rl.erase(swp(left)), rl.erase(swp(right));
        ++tans;
        int pl = 2;
        if (left.first <= mxx && mxx <= left.second)
            --pl;
        if (right.first <= mxx && mxx <= right.second)
            --pl;
        if (!pl)
            break;
        for (int i = tk + 1; i <= tk + pl; ++i)
            ans[i] = tans;
        tk += pl;
    }
    while (q--)
    {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
    return 0;
}
