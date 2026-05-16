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
using namespace std;
int n,q,l[262144],r[262144],k;
vector <pair <int,int>> v;
void speed()
{
 ios_base::sync_with_stdio(false);
 cin.tie(0);
}
int check(vector <pair <int,int>> v)
{
    int ans=0;
    for(int i=0;i<v.size();i++)
    {
        int mx=0,mn=1e9;
        for(int j=i;j<v.size();j++)
        {
            mx=max(mx,v[j].first);
            mn=min(mn,v[j].second);
            if(mx>mn)break;
            ans=max(ans,j-i+1);
            if(ans>=10)return ans;
        }
    }
    return ans;
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
        v.push_back({l[i],r[i]});
    }
    sort(v.begin(),v.end());
        cin>>k;
        int i=0,j=v.size()-1,op=0;
        while(check(v)<k)
        {
            swap(v[i].second,v[j].first);
            i++;
            j--;
            op++;
        }
        cout<<op<<endl;
    return 0;
}
/*
6 6
25 30
15 29
7 12
8 14
4 5
16 23
6
*/
