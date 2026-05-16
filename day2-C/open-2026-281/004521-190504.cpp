#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#define ll long long
#define X first
#define Y second
#define endl '\n'
using namespace std;

void speed()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}
int n,q;
const int MAXN=200100;
int l[MAXN],r[MAXN],k[MAXN];
void read()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>l[i]>>r[i];
    }
    for(int i=1;i<=q;i++)
    {
        cin>>k[i];
    }
}
signed main()
{
    speed();
    read();
    for(int i=1;i<=q;i++)
    {
        int t=k[i];
        if(t%2==0)t++;
        cout<<(t-1)/2<<' ';
    }
    return 0;
}