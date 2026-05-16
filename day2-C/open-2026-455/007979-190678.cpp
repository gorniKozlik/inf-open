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

vector <pair<int, int>> a;

void solve()
{
    int n, q;
    cin >> n >> q;
    a.resize(n);
    for (auto& i : a) cin >> i.first >> i.second;
    for (int i = 0; i < q; i++)
    {
        int k;
        cin >> k;
        cout << k / 2 << ' ';
    }


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
