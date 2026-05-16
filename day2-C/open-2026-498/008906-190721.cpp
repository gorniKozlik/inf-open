#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define ins insert

using namespace std;

struct ve {
    int v1;
    int v2;
};

int32_t main()
{
    int n, m, i, j, k, k1, k2, k3, x, x1, x2, x3, t, g;
    cin >> n >> m;
    vector <ve> a;
    for (i = 0; i < n; i++) {
        cin >> x1 >> x2;
        a.pb({x1, x2});
    }
    vector <int> ans;
    int zero = 0;
    for (i = 0; i < m; i++) {
        cin >> x;
        ans.pb(x/2);
    }
    for (auto z : ans)
        cout << z << ' ';
    return 0;
}
