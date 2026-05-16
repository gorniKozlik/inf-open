# include <iostream>
# include <algorithm>
# include <vector>
# include <set>
using namespace std;

template<class T> void chmin(T& A, const T& B) {A=min(A,B);}

const int MAX=4e5+11,INF=1e9;

int n,q;
pair<int,int> a[MAX];
int pref[MAX];
int suf[MAX];
bool lp[MAX];

int tree[MAX*4];

void update(int le, int ri, int d, int v=1, int l=1, int r=n*2)
{
    if(ri<l or r<le) return ;
    if(le<=l and r<=ri)
    {
        tree[v]+=d;
        return ;
    }

    int mid=(l+r)/2;
    update(le,ri,d,v*2,l,mid);
    update(le,ri,d,v*2+1,mid+1,r);
}

int query(int pos, int v=1, int l=1, int r=n*2)
{
    int ans=tree[v];
    if(l==r) return ans;

    int mid=(l+r)/2;
    if(pos<=mid) return ans+query(pos,v*2,l,mid);
    else return ans+query(pos,v*2+1,mid+1,r);
}

int current[MAX];
int ans[MAX];
vector<int> toAdd[MAX];
vector<int> toRem[MAX];

void solve()
{
    for(int i=1;i<=n;i++) ans[i]=INF;

    for(int i=1;i<=n*2;i++)
    {
        //cout<<i<<":"<<query(i)<<"->"<<k<<"\n";
        if(lp[i]==0)
        {
            int curr=query(i);
            current[i]=curr;
            ans[curr]=0;

            int cntL=pref[i-1],cntR=suf[i+1];
            int add=min(cntL,cntR);
            toAdd[curr].push_back(i);
            toRem[curr+(add+1)*2].push_back(i);
            if(cntL<cntR)
            {
                //cout<<"->"<<curr+add*2+1<<"\n";
                chmin(ans[curr+add*2+1],add+1);
            }
        }
        else
        {
            int curr=query(i);
            current[i]=curr;
            ans[curr]=0;

            int cntL=pref[i-1],cntR=suf[i+1];
            int add=min(cntL,cntR);
            toAdd[curr].push_back(i);
            toRem[curr+(add+1)*2].push_back(i);
            if(cntL>cntR)
            {
                //cout<<"->"<<curr+add*2+1<<"\n";
                chmin(ans[curr+add*2+1],add+1);
            }
        }
    }

    set<pair<int,int>> s[2];
    for(int i=1;i<=n;i++)
    {
        int p=i%2;
        for(int x: toAdd[i]) s[p].insert({current[x],x});
        for(int x: toRem[i]) s[p].erase({current[x],x});

        if(s[p].size()>0)
        {
            int c=(--s[p].end())->first;
            int sc=(i-c)/2;
            chmin(ans[i],sc);
        }
    }

    for(int i=n-1;i>=1;i--) chmin(ans[i],ans[i+1]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>q;
    vector<pair<int,int>> cmpr;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].first>>a[i].second;
        cmpr.push_back({a[i].first,i});
        cmpr.push_back({a[i].second,-i});
    }
    sort(cmpr.begin(),cmpr.end());
    int last=-1,cnt=0;
    for(pair<int,int> pa: cmpr)
    {
        if(pa.first!=last)
        {
            last=pa.first;
            cnt++;
        }
        if(pa.second>0)
        {
            a[pa.second].first=cnt;
            lp[cnt]=1;
        }
        else a[-pa.second].second=cnt;
    }

    for(int i=1;i<=n;i++)
    {
        //cout<<a[i].first<<" "<<a[i].second<<"\n";
        pref[a[i].second]++;
        suf[a[i].first]++;
        update(a[i].first,a[i].second,1);
    }
    for(int i=1;i<=n*2;i++) pref[i]+=pref[i-1];
    for(int i=n*2+1;i>=1;i--) suf[i]+=suf[i+1];

    solve();
    while(q--)
    {
        int k;
        cin>>k;
        cout<<ans[k]<<" ";
    }
    cout<<"\n";

    return 0;
}

/*
6 1
25 30
15 29
7 12
8 14
4 5
16 23
4
*/
