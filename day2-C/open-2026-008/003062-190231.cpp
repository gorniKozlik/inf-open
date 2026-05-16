// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector <int> a;
    vector <pair<int, int>> flow;
    for (size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        flow.emplace_back(x, y);
        a.push_back(x);
        a.push_back(y);
    }
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
    for (auto& i : flow)
    {
        i.first = lower_bound(a.begin(), a.end(), i.first) - a.begin();
        i.second = lower_bound(a.begin(), a.end(), i.second) - a.begin();
    }
    int m = a.size();
    vector <int> over(m);
    for (size_t i = 1; i < m; i++)
    {
        for (auto& j : flow)
        {
            if (j.first < i && i <= j.second)
            {
                over[i]++;
            }
        }
    }
    for (size_t i = 0; i < q; i++)
    {
        int ki;
        cin >> ki;
        int ans = 1e9;
        for (size_t j = 1; j < m; j++)
        {
            int ov = over[j];
            int l = j - ov;
            int r = m - j - ov;
            int xg = min(l, r);
            int ng = ki - ov;
            ng = max(ng, 0);
            if (ng <= xg)
            {
                ans = min(ans, (ng + 1) / 2);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
