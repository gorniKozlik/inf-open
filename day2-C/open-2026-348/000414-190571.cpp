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

const int maxn=2e5+5;
int n,q;
line a[maxn];
int dp[maxn];

void precomp()
{
    for(int i=2;i<=n;i+=2)
    {
        dp[i]=i/2;
        dp[i+1]=i/2;
    }
}

void read()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>a[i].l>>a[i].r;

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

5 5
1 2
3 5
6 7
8 10
11 12
1 2 3 4 5

**/
