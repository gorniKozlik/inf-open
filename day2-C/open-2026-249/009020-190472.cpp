#include <bits/stdc++.h>
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2")

using namespace std;

#define ll long long
#define ld long double
#define mod7 int(1e9 + 7)
#define mod9 int(1e9 + 9)
#define uscor ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mod int(998244353)
using pi = pair<int, int>;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist(-mod7, mod7);

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pi> seg(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> seg[i].first >> seg[i].second;
    }
    while (m--)
    {
        int k;
        cin >> k;
        if (n == 1)
        {
            cout << 0 << '\n';
            continue;
        }
        if (k == 1 || k == 2 || k == 3)
        {
            cout << 1 << '\n';
        }
        else {
            k -= 3;
            cout << k / 2 + 1 + k % 2 << '\n';
        }
    }
    return 0;
}