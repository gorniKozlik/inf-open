#include <iostream>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <cmath>
#include <map>
#include <set>
#include <deque>
#include <random>
#include <algorithm>
#include <unordered_map>

using namespace std;
using ll = long long int;
using ld = long double;
using ull = unsigned long long int;
using uint = unsigned int;

const ll linf = 1e18 + 7;
const int inf = 1e9 + 7;
const ll M = 998244353;
const ld PI = 2 * asin(1);

#define sz(v) (int)v.size()
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend();
#define nr nullptr
#define br(v) {cout << v; return;}

vector <int> a;

void solve()
{
    int T, n, m;
    cin >> T >> n >> m;
    a.resize(n);
    set<int> c;
    for (auto& i : a) cin >> i;
    for (int i = 0; i < n; i++)
    {
        c.insert(a[i] % 2);
    }
    if (sz(c) > 1)
    {
        br("No");
        return;
    }
    cout << "Yes\n";
    if (T == 1)
    {
        return;
    }
    string s;
    cin >> s;
    int best = 0, d = 0;
    for (int t = 0; t < 2 * m; t++)
    {
        if (a[0] == a[1] && a[0] > d)
        {
            best = t;
            d = a[0];

        }
        if (s[0] == 'L')
        {
            a[0]--;
            if (a[0] == 1) s[0] = 'R';
        }
        else
        {
            a[0]++;
            if (a[0] == m) s[0] = 'L';
        }
        if (s[1] == 'L')
        {
            a[1]--;
            if (a[1] == 1) s[1] = 'R';
        }
        else
        {
            a[1]++;
            if (a[1] == m) s[1] = 'L';
        }
    }
    cout << d << '\n';
    if (T == 2) return;
    cout << 1 << '\n';
    cout << best << ' ' << d;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    //freopen("input.txt", "r", stdin);
    
    int _ = 1;
    while (_--)
    {
        solve();
        cout << '\n';
    }
}
