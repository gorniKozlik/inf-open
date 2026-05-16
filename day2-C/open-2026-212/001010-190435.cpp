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

    vpii seg(n);
    for (int i = 0; i < n; ++i)
        cin >> seg[i].first >> seg[i].second;

    sort(seg.begin(), seg.end());
    
    int k;
    cin >> k;

    int ans = 0;
    int j = n - 1;
    for (int i = 0; i < n; ++i)
    {
        if (seg[i].second < seg[j].first)
        {
            ans++;
            j--;
        }
    }

    cout << ans;
}