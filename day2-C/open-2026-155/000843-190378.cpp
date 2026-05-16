#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
void speed()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
struct cell
{
    int l,r,ind;
};
struct ver
{
    int pos,type,ind,cur,tol,tor;
};
bool cmp(ver a1,ver a2)
{
    if(a1.pos!=a2.pos)return a1.pos<a2.pos;
    if(a1.type!=a2.type)return a1.type<a2.type;
    return a1.ind<a2.ind;
}
bool cmp2(ver a1,ver a2)
{
    return a1.cur>a2.cur;
}
int n,q,b[400005],otg[400005];
cell a[400005];
ver c[400005];
void prec()
{
    sort(c+1,c+n*2+1,cmp);
    int br=0,to=1;
    for(int i=1;i<=n*2;i++)
    {
        to=max(to,i);
        while(c[to].pos==c[to+1].pos&&c[to+1].type==1)
        {
            to++;
            br++;
        }
        if(i==to&&c[i].type==1)br++;
        c[i].cur=br;
        c[i].tol=i-br;
        c[i].tor=n*2-2*br+1-c[i].tol;
        if(c[i].type==2)br--;
        //cout<<br<<" "<<c[i].pos<<" "<<c[i].type<<" "<<cur[i]<<" "<<tol[i]<<" "<<tor[i]<<endl;
    }
    /*cout<<endl;
    for(int i=1;i<=n*2;i++)
    {
        cout<<cur[i]<<" "<<tol[i]<<" "<<tor[i]<<endl;
    }*/
}
void resh()
{
    sort(c+1,c+n*2+1,cmp2);
    int to=1;
    for(int i=1;i<=n*2;i++)
    {
        for(int j=to;j<=c[i].cur+min(c[i].tol,c[i].tor);j++)
        {
            otg[j]=max(0,j-c[i].cur+1)/2;
        }
        to=max(to,c[i].cur+min(c[i].tol,c[i].tor)+1);
    }
    for(int i=1;i<=q;i++)
    {
        cout<<otg[b[i]]<<" ";
    }
    cout<<endl;
}
void read()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].l>>a[i].r;
        a[i].ind=i;
        c[i*2-1].pos=a[i].l;
        c[i*2-1].ind=i;
        c[i*2-1].type=1;
        c[i*2].ind=i;
        c[i*2].pos=a[i].r;
        c[i*2].type=2;
    }
    for(int i=1;i<=q;i++)
    {
        cin>>b[i];
    }
    cout<<endl;
    prec();
    resh();
}
int main()
{
    speed();
    read();
	return 0;
}
