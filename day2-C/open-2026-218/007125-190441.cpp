#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

inline pair<int, int> swp(pair<int, int> x)
{
    return {x.second, x.first};
}

int mxk(set<pair<int, int>>& v)
{
    set<pair<int, int>> ev;
    for (pair<int, int> i : v)
        ev.insert({i.first, 1}), ev.insert({i.second, -1});
    int tk = 0;
    int res = 0;
    for (pair<int, int> i : ev)
    {
        tk += i.second;
        res = max(res, tk);
    }
    return res;
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
    set<pair<int, int>> vs;
    for (pair<int, int> i : v)
        vs.insert(i);
    vector<int> ans(n + 1, n);
    int tans = 0;
    int tk = 0;
    while (true)
    {
        int ntk = mxk(vs);
        for (int i = tk + 1; i <= ntk; ++i)
            ans[i] = tans;
        if (tk != 0 && ntk - tk > 2)
            exit(3);
        tk = ntk;
        if (ntk == n)
            break;
        pair<int, int> left = swp(*rl.begin()), right = *lr.rbegin();
        if (left.second > right.first)
            break;
        lr.erase(left), lr.erase(right);
        rl.erase(swp(left)), rl.erase(swp(right));
        vs.erase(left), vs.erase(right);
        vs.insert({left.first, right.second});
        vs.insert({left.second, right.first});
        ++tans;
    }
    while (q--)
    {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
    return 0;
}
