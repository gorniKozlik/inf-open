#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct event
{
    int t,x;
    bool operator<(const  event &a) const
    {
        return x<a.x;
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
        E.push_back({1,r+1});
    }
    sort(E.begin(),E.end());
    int a=0,b=n,c=0;
    int x=0;
    vector<pair<int,int>> S;
    for(auto &[t,y]:E)
    {
        if(t==0)
        {
            b--;
            c++;
        }
        else
        {
            a++;
            c--;
        }
        x=max(x,c);
        S.push_back({c+2*min(a,b),c});
    }
    sort(S.begin(),S.end());
    vector<int> pref(S.size());
    pref.back()=S.back().second;
    for(int i=(int)S.size()-2;i>=0;i--)
    {
        pref[i]=max(pref[i+1],S[i].second);
    }
    while(q--)
    {
        cin >> k;
        if(k<=x)
        {
            cout << "0 ";
        }
        else
        {
            int it=upper_bound(S.begin(),S.end(),pair{k-1,0})-S.begin()+1;
            if(it==(int)S.size() || S[it].first<k)
            {
                cout << (S.back().first-S.back().second)/2+(k-S.back().first)+1 << " ";
            }
            else
            {
                cout << (k-pref[it]+1)/2 << " ";
            }
        }
    }
    return 0;
}
