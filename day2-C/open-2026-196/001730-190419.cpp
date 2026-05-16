//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;
#define int long long
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

vector<int> v,d;
void build(int ind,int l,int r)
{
    if (r-l==1)
    {
        d[ind] = v[l];
        return;
    }
    int m = (r+l)/2;
    build(2*ind+1,l,m);
    build(2*ind+2,m,r);
    d[ind] = max(d[2*ind+1],d[2*ind+2]);
}
int get(int ind,int l,int r,int ql,int qr)
{
    if (l>=qr||r<=ql) return -1;
    if (l>=ql&&r<=qr) return d[ind];
    int m = (r+l)/2;
    return max(get(2*ind+1,l,m,ql,qr),get(2*ind+2,m,r,ql,qr));
}
signed main()
{
    int n,q;
    cin >> n >> q;
    vector<int> l(n),r(n);
    for (int i=0;i<n;i++)
    {
        cin >> l[i] >> r[i];
    }
    vector<int> t;
    for (int i=0;i<n;i++)
    {
        t.push_back(l[i]);
        t.push_back(r[i]);
    }
    sort(t.begin(),t.end());
    sort(r.begin(),r.end());
    sort(l.begin(),l.end());
    vector<int> w(2*n-1);
    for (int i=0;i<2*n-1;i++)
    {
        int a = upper_bound(r.begin(),r.end(),t[i])-r.begin();
        int b = n-(lower_bound(l.begin(),l.end(),t[i+1])-l.begin());
        w[i] = min(a,b);
    }
    vector<pair<int,int>> p;
    for (int i=0;i<n;i++)
    {
        p.push_back({l[i],1});
        p.push_back({r[i],-1});
    }
    sort(p.begin(),p.end());
    int s=0;
    vector<int> ww(2*n-1);
    for (int i=0;i<2*n-1;i++)
    {
        s += p[i].second;
        ww[i] = s;
    }
    vector<pair<int,int>> e(2*n-1);
    for (int i=0;i<2*n-1;i++)
    {
        e[i] = {w[i]*2+ww[i],ww[i]};
    }
    sort(e.begin(),e.end());
    int m = 2*n-1;
    v.resize(m);
    for (int i=0;i<m;i++) v[i] = e[i].second;
    vector<int> g(m);
    for (int i=0;i<m;i++) g[i] = e[i].first;
    d.resize(4*m);
    build(0,0,m);
    for (auto i:w)
    {
        //cout << i << " ";
    }
    //cout << "\n";
    for (int i=0;i<q;i++)
    {
        int k;
        cin >> k;
        int u = lower_bound(g.begin(),g.end(),k)-g.begin();
        int y = get(0,0,m,u,m);
        if (y>=k)
        {
            cout << 0 << "\n";
        }
        else
        {
            cout << (k-y+1)/2 << "\n";
        }
    }
}
