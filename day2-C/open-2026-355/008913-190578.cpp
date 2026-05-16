#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <iomanip>
#include <set>
#include <cstring>
#define control cout<<"e ne"<<endl;
#define endl '\n'
using namespace std;
int n,q,l[262144],r[262144],k,used[3001],comp[262144],ans[3001];
int v[3001];
vector <pair <int,int>> x;
void speed()
{
 ios_base::sync_with_stdio(false);
 cin.tie(0);
}
signed main()
{
    /*
    #ifdef ONLINE_JUDGE
    freopen("txt.in","r",stdin)
    freopen("txt.out","w",stdout)
    #endif
    */
    speed();
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>l[i]>>r[i];
        x.push_back({l[i],r[i]});
    }
    sort(x.begin(),x.end());
    for(int i=0;i<x.size();i++)
    {
        int mn=1e9,mx=0;
        int ans=0;
        for(int j=i;j<x.size();j++)
        {
            mn=min(mn,x[j].second);
            mx=max(mx,x[j].first);
            if(mx>mn)break;
            ans=max(ans,j-i+1);
        }
        v[i+1]=ans;
    }
    vector <int> d;
    for(int i=1;i<=n;i++)d.push_back(v[i]);
    sort(d.rbegin(),d.rend());
    int sum=1;
    for(int i=0;i<d.size();i++)
    {
        for(int j=sum;j<=sum+d[i]-1;j++)ans[j]=i;
        sum+=d[i];
    }
    while(q--)
    {
        cin>>k;
        cout<<ans[k]<<" ";
    }
    cout<<endl;
    return 0;
}
