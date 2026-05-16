#include<bits/stdc++.h>
using namespace std;
int n, q;
int l[200005], r[200005];
void read()
{
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> l[i] >> r[i];
}
void solve()
{
    int k;
    for(int i = 1; i <= q; i++)
    {
        cin >> k;
        cout << k/2 << " ";
    }
    cout << endl;
}
int main()
{
    read();
    solve();
    return 0;
}

