#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
void speed()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
const int maxn=2e5+10;
int n,q,minn=0;
int l[maxn],r[maxn];
int z[maxn];
vector<pair<int,int>> s;
int otg[maxn];
vector<pair<int,int>> v;
void read()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>l[i]>>r[i];
        v.push_back({l[i],r[i]});
        v.push_back({r[i],l[i]});
    }
    for(int i=1;i<=q;i++)
    {
        cin>>z[i];
        minn=max(minn,z[i]);
    }
    //sort(v.begin(),v.end());
}
int main()
{
    speed();
    read();
    /*int ans=0;
    for(int i=1;i<=minn;i++)
    {
        otg[i]=1e9;
    }
    while(ans<=n)
    {
        int br=0,maxbr=0;
        s.clear();
        s.shrink_to_fit();
        for(auto i:v)
        {
            if(i.first<i.second)
            {
                s.push_back({i.first,+1});
                s.push_back({i.second+1,-1});
            }
        }
        sort(s.begin(),s.end());
        for(auto i:s)
        {
            br+=i.second;
            maxbr=max(maxbr,br);
        }
        for(int i=1;i<=maxbr;i++)
        {
            otg[i]=min(otg[i],ans);
        }
        if(maxbr>=minn)
        {
            break;
        }
        int p=v.size()-1,find1=-1,find2=-1,j=0;
        for(auto i:v)
        {
            if(i.second!=v[p].first)
            {
                //cout<<"!!!"<<' '<<i.first<<' '<<i.second<<' '<<v[p].first<<' '<<v[p].second<<endl;
                find1=v[j].second;
                find2=v[p].second;
                v[j].second=v[p].first;
                v[p].second=v[j].first;
                break;
            }
            else
            {
                p--;
            }
            j++;
        }
        j=0;
        for(auto i:v)
        {
            if(i.first==find1)
            {
                v[j].second=find2;
            }
            if(i.first==find2)
            {
                v[j].second=find1;
            }
            j++;
        }
        ans++;
    }
    for(int i=1;i<=q;i++)
    {
        cout<<otg[z[i]]<<' ';
    }*/
    otg[1]=0;
    for(int i=2;i<=n;i+=2)
    {
        otg[i]=otg[i-1]+1;
        otg[i+1]=otg[i];
    }
    for(int i=1;i<=q;i++)
    {
        cout<<otg[z[i]]<<' ';
    }
    return 0;
}

