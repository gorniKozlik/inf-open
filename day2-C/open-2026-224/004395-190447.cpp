#include <bits/stdc++.h>
#define endl '\n'
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#pragma GCC optimize("O3" , "Ofast" , "unroll-loops" , "fast-math")


using namespace std;

const int MAXN = 2e5;
int l[MAXN + 5], r[MAXN + 5];


signed main()
{
    srand(time(0));
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n, q; cin >> n >> q;

    for(int i = 1; i <= n; i++)
    {
        cin >> l[i] >> r[i];
    }

    while(q--)
    {
        int x;
        cin >> x;
        cout << x  / 2 << endl;
    }

    //double  x; cin >> x;
    //cout << fixed << setprecision(6) << x << endl;

    return 0;
}
