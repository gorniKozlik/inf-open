#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vpii = vector<pair<int, int>>;

int main()
{
    int n, q;
    cin >> n >> q;

    vi l(n), r(n), all;
    for (int i = 0; i < n; ++i)
    {
        cin >> l[i] >> r[i];
        all.push_back(l[i]);
        all.push_back(r[i]);
    }
    
    int k;
    cin >> k;

    sort(all.begin(), all.end());

    int last = all[n - 1], first = all[n];

    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (r[i] < first || l[i] > last)
            cnt++;
    }

    cout << cnt / 2;
}