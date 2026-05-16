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
signed main()
{
    speed();
    int T,n,m;
    cin>>T>>n>>m;
    vector<pair<int,bool>> v(n);
    for(int i=0;i<n;i++)
    {
        cin>>v[i].X;
    }
    for(int  i=0;i<n;i++)
    {
        char c;
        cin>>c;
        if(c=='R')v[i].Y=0;
        else v[i].Y=1;
    }
    if(m==1)
    {
        cout<<"Yes\n1\n";
        return 0;
    }
    if(m%2==0)
    {
        cout<<"No"<<endl;
        return 0;
    }
    cout<<"Yes"<<endl<<m/2+1<<endl;
    cout<<m/2<<' '<<m/2+1<<endl;
    return 0;
}