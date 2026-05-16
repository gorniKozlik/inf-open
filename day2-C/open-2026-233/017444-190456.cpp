#include<bits/stdc++.h>
using namespace std;
int n, q;
int l[200005], r[200005];
bool cmp(int x, int y)
{
    return l[x] < l[y];
}
vector <int> v;
void read()
{
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> l[i] >> r[i];
    for(int i = 1; i <= n; i++)
        v.push_back(i);
    sort(v.begin(), v.end(), cmp);
}
void solve()
{
    int k;
    cin >> k;
    int ans = 0;
    for(int i = 1; i < n; i++)
    {
        if(l[v[i]] > r[v[i-1]])
        {
            ans++;
            int a = l[v[i-1]];
            int b = r[v[i-1]];
            int c = l[v[i]];
            int d = r[v[i]];
            r[v[i-1]] = d;
            l[v[i]] = b;
            r[v[i]] = c;
        }
    }
    cout << ans << endl;
}
int main()
{
    read();
    solve();
    return 0;
}

