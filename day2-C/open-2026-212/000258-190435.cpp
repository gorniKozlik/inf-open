#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int main()
{
    int n, q;
    cin >> n >> q;

    vi lr(2 * n);
    for (int &x : lr)
        cin >> x;
        
    while (q-- > 0)
    {
        int k;
        cin >> k;

        cout << k / 2 << ' ';
    }
}