#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct event
{
    int t,x;
    bool operator<(const  event &a) const
    {
        return x<a.x || (x==a.x && t<a.t);
    }
};
struct point
{
    int x,y,z;
};
vector<event> E;
int main()
{
    int n,q,l,r,k;
    cin >> n >> q;
    for(int i=0;i<n;i++)
    {
        cin >> l >> r;
        E.push_back({0,l});
        E.push_back({1,r});
    }
    sort(E.begin(),E.end());
    int a=0,b=n,c=0;
    vector<point> S;
    for(auto &[t,y]:E)
    {
        if(t==0)
        {
            b--;
            c++;
        }
        S.push_back({c,2*min(a,b),0});
        if(t==0 && a>b)
        {
            S.back().z++;
        }
        if(t==1 && b>a)
        {
            S.back().z++;
        }
        if(t==1)
        {
            a++;
            c--;
        }
    }
    /**sort(S.begin(),S.end());
    vector<int> pref(S.size());
    pref.back()=S.back().second;
    for(int i=(int)S.size()-2;i>=0;i--)
    {
        pref[i]=max(pref[i+1],S[i].second);
    }**/
    while(q--)
    {
        cin >> k;
        int ans=1e9;
        for(auto &[x,y,z]:S)
        {
            if(k<=x)
            {
                ans=0;
            }
            else if(k<=x+y)
            {
                ans=min(ans,(k-x+1)/2);
            }
            else if(k<=x+y+z)
            {
                ans=min(ans,y/2+1);
            }
        }
        cout << ans << " ";
    }
    return 0;
}
