#include<bits/stdc++.h>
using namespace std;

void speed()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
const int maxn=1e6+5;

int n,q;
pair<int,int> a[maxn];
int k[maxn];
map<int,int> mp;
int cnt=0;
int l[maxn];
int r[maxn];
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

int ans[maxn];
int p[maxn],s[maxn];
vector<pair<int,int> > s2;
struct help
{
    int first,second,b;
    help(){}
    help(int _l,int _r,int _b)
    {
        first=_l;
        second=_r;
        b=_b;
    }
};

vector<help> s1;

bool cmp(pair<int,int> p1,pair<int,int> p2)
{
    return p1.second<p2.second;
}

bool cmp1(help h1,help h2)
{
    return h1.second<h2.second;
}

int t[maxn];
void update(int i,int l,int r,int id,int vl)
{
    if(l==r)
    {
        t[i]=min(t[i],vl);
        return;
    }

    int m=(l+r)/2;
    if(id<=m)update(i*2,l,m,id,vl);
    else update(i*2+1,m+1,r,id,vl);

    t[i]=min(t[i*2],t[i*2+1]);
}

int query(int i,int l,int r,int ql,int qr)
{
    if(ql>qr)return 1e9;
    if(ql<=l&&r<=qr)return t[i];
    int m=(l+r)/2;
    return min(query(i*2,l,m,ql,min(qr,m)),query(i*2+1,m+1,r,max(m+1,ql),qr));
}

void solve()
{
    for(int i=1;i<=4*n;i++)
        t[i]=1e9;
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

    int zero=0;
    for(int i=1;i<=cnt;i++)
    {
        int lf=p[i-1];
        int rt=s[i+1];

        int curr=n-lf-rt;
        zero=max(zero,curr);

        int lfon=l[i];
        int rton=r[i];

        int c2=min(lf,rt);
        lf-=c2;
        rt-=c2;
        int m1=curr+c2*2;
        s2.push_back({curr,m1});

        int c1=min(lfon,lf)+min(rton,rt);
        s1.push_back({m1,m1+c1,c2});

        //cout<<i<<" "<<curr<<" "<<m1<<" "<<m1+c1<<" "<<c2<<endl;
    }

    sort(s2.begin(),s2.end(),cmp);
    sort(s1.begin(),s1.end(),cmp1);

    int j1=s1.size()-1;
    int j2=s2.size()-1;
    int m1=-1e9,m2=-1e9;
    for(int i=n;i>=1;i--)
    {
        if(zero>=i)
        {
            ans[i]=0;
            continue;
        }

        while(j1&&s1[j1].second>=i)
        {
            update(1,1,n,s1[j1].first,s1[j1].b-s1[j1].first);
            /////////
            j1--;
        }

        ans[i]=min(ans[i],i+query(1,1,n,1,i));

        while(j2&&s2[j2].second>=i)
        {
            m2=max(m2,s2[j2].first);
            j2--;
        }

        if(m2<=i)
        {
            ans[i]=min(ans[i],(i-m2)/2+(i-m2)%2);
        }

        //cout<<i<<" "<<m1<<" "<<m2<<endl;
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
