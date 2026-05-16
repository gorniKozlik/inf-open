#include<bits/stdc++.h>
using namespace std;

void speed()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int n,q;
pair<int,int> a[200001];
int k[200001];
map<int,int> mp;
int cnt=0;
int l[200001];
int r[200001];
void read()
{
    vector<int> v;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].first>>a[i].second;
        v.push_back(a[i].first);
        v.push_back(a[i].second);
    }

    sort(v.begin(),v.end());

    for(int i=0;i<v.size();i++)
    {
        if(i==0||v[i-1]!=v[i])cnt++;
        mp[v[i]]=cnt;
    }

    for(int i=1;i<=n;i++)
        a[i].first=mp[a[i].first],
        a[i].second=mp[a[i].second];

    //for(int i=1;i<=n;i++)
    //    cout<<a[i].first<<" "<<a[i].second<<endl;
    for(int i=1;i<=q;i++)
        cin>>k[i];
}

int ans[200001];
int p[200001],s[200001];

void solve()
{
    for(int i=1;i<=n;i++)
    {
        ans[i]=n;
        l[a[i].first]++;
        r[a[i].second]++;
    }

    for(int i=1;i<=cnt;i++)
        p[i]=p[i-1]+r[i];
    for(int i=cnt;i>=1;i--)
        s[i]=s[i+1]+l[i];

    for(int i=1;i<=cnt;i++)
    {
        int lf=p[i-1];
        int rt=s[i+1];

        int curr=n-lf-rt;
        for(int j=1;j<=curr;j++)
            ans[j]=0;
        int lfon=l[i];
        int rton=r[i];
        int sw=0;
        while(lf&&rt)
        {
            lf--;
            rt--;
            sw++;
            ans[curr+1]=min(ans[curr+1],sw);
            ans[curr+2]=min(ans[curr+2],sw);
            curr+=2;
        }

        while(lfon&&lf)
        {
            lfon--;
            lf--;
            sw++;
            ans[curr+1]=min(ans[curr+1],sw);
            curr++;
        }

        while(rton&&rt)
        {
            rton--;
            rt--;
            sw++;
            ans[curr+1]=min(ans[curr+1],sw);
            curr++;
        }
    }

    for(int i=1;i<=q;i++)
        cout<<ans[k[i]]<<" ";
    cout<<endl;
}

int main()
{
    speed();
    read();
    solve();
    return 0;
}
