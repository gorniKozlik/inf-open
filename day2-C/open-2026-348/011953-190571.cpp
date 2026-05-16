#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

void speed()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct line
{
    int l,r;
    line(){};
    line(int l11,int r11)
    {
        l=l11;
        r=r11;
    }
};

struct point
{
    int x,type;
    point(){};
    point(int x11,int tp)
    {
        x=x11;
        type=tp;
    }
};

const int maxn=2e5+5;
int n,q;
line a[maxn];
int dp[maxn];
int last=0;

bool cmp(line l1,line l2)
{
    if(l1.l!=l2.l)
        return l1.l<l2.l;
    return l1.r<l2.r;
}

bool cmp_point(point p1,point p2)
{
    if(p1.x!=p2.x)
        return p1.x<p2.x;
    return p1.type>p2.type;
}

void solve(int curr)
{
    //sort(a+1,a+n+1,cmp);

    vector<point>v;
    for(int i=1;i<=n;i++)
    {
        v.push_back({a[i].l,1});
        v.push_back({a[i].r,-1});
    }

    sort(v.begin(),v.end(),cmp_point);

    int cnt=0,ans=0;
    for(point i : v)
    {
        cnt+=i.type;
        ans=max(ans,cnt);
    }

    for(int i=last+1;i<=ans;i++)
        dp[i]=curr;
    last=ans;
}

void precomp()
{
    //solve(0);

    int cnt=0;
    /*for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j)
                continue;

            if(a[i].l<a[j].l && a[i].r>a[j].r)
            {
                int z=a[i].r;
                a[i].r=a[j].r;
                a[j].r=z;

                cnt++;
                solve(cnt);
            }
        }
    }*/

    //for(int i=1;i<=n;i++)
      //  cout<<a[i].l<<' '<<a[i].r<<endl;

    sort(a+1,a+n+1,cmp);

    solve(cnt);

    //cout<<last<<endl;
    int lft=1,rght=n;
    while(last<n && lft<=rght)
    {
        if(lft==rght)
            rght++;
        int z=a[lft].r;
        a[lft].r=a[rght].l;
        if(a[lft].l>a[lft].r)
            swap(a[lft].l,a[lft].r);
        a[rght].l=z;
        if(a[rght].l>a[rght].r)
            swap(a[rght].l,a[rght].r);

        cnt++;
        solve(cnt);

        /*cout<<lft<<endl;
        for(int i=1;i<=n;i++)
            cout<<a[i].l<<' '<<a[i].r<<endl;*/

        lft++;
        rght--;
    }
    //cout<<"last "<<last<<endl;
}

void read()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].l>>a[i].r;
    }

    precomp();

    int k;
    for(int i=0;i<q;i++)
    {
        cin>>k;
        cout<<dp[k]<<' ';
    }
    cout<<endl;
}

int main()
{
    speed();
    read();
    return 0;
}

/**
3 3
2 10
3 5
6 11
1 2 3
**/
