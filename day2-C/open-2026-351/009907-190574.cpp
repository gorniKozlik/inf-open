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
    int x,y;
    bool operator<(const point &a) const
    {
        return y<a.y;
    }
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
    int s=0;
    vector<int> R(n+1,1e9);
    for(auto &[t,y]:E)
    {
        if(t==0)
        {
            b--;
            c++;
        }
        S.push_back({c,c+2*min(a,b)});
        s=max(s,c);
        if(t==0 && a>b)
        {
            R[c+2*min(a,b)+1]=min(R[c+2*min(a,b)+1],min(a,b)+1);
        }
        if(t==1 && b>a)
        {
            R[c+2*min(a,b)+1]=min(R[c+2*min(a,b)+1],min(a,b)+1);
        }
        if(t==1)
        {
            a++;
            c--;
        }
    }
    sort(S.begin(),S.end());
    vector<int> pref(S.size());
    pref.back()=S.back().x;
    for(int i=(int)S.size()-2;i>=0;i--)
    {
        pref[i]=max(pref[i+1],S[i].x);
    }
    while(q--)
    {
        cin >> k;
        if(k<=s)
        {
            cout << "0 ";
            continue;
        }
        int ans=R[k];
        int it=lower_bound(S.begin(),S.end(),point{0,k})-S.begin();
        if(it<(int)S.size())
        {
            ans=min(ans,(k-S[it].x+1)/2);
        }
        cout << ans << " ";
    }
    return 0;
}
