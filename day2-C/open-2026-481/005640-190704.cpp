#include <bits/stdc++.h>
#define endl "\n"

using namespace std;

void speed()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}


const int MAXN = 4e5+5;///2*n

int n,q;
pair<int,int> p[MAXN];

bool cmp(pair<int,int> p1, pair<int,int > p2)
{
    return p1.second < p2.second;
}
bool cmpse(pair<int,int> p1, pair<int,int> p2)
{
    if(p1.first == p2.first) return p1.second > p2.second;
    return p1.first < p2.first;
}
int used[MAXN];
map<int,int>mymap;
void compress()
{
    vector<int>v;
    for(int i = 1; i <= n; i++)
    {
        v.push_back(p[i].first);
        v.push_back(p[i].second);
    }

    sort(v.begin(),v.end());
    mymap[v[0]] = 1;
    int idx = 1;
    for(int i = 1; i < v.size(); i++)
    {
        if(v[i-1] != v[i]) idx++;
        mymap[v[i]] = idx;
    }
    for(int i = 1; i <= n; i++)
    {
        p[i].first = mymap[p[i].first];
        p[i].second = mymap[p[i].second];
    }
}

int st[MAXN],fn[MAXN];
void read()
{
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
    {
        cin >> p[i].first >> p[i].second;
    }
    compress();
    for(int i = 1; i <= n; i++)
    {
        st[p[i].first]++;
        fn[p[i].second]++;
    }
}

int dul[MAXN];
struct Thrice
{
    bool b0;
    int mindel2;
    int raz;
};
Thrice tree[4*MAXN];
int ql,qr;
pair<int,int>val;


//long long dp[MAXN][MAXN];

void update(int v, int l, int r)
{
    if(r < ql || qr < l || l > r) return;
    if(ql <= l && r <= qr)
    {
        if(val.first == 1) tree[v].b0 = 1;
        if(val.first == 2) tree[v].mindel2 = max(tree[v].mindel2, val.second);
        if(val.first == 3) tree[v].raz = max(tree[v].raz,val.second);
        return;
    }
    int mid = (l+r)/2;
    update(v*2+0,l,mid+0);
    update(v*2+1,mid+1,r);//bez subirane
}

int query(int v, int l, int r)
{
    int c = 1e9;
    if(tree[v].b0) c = 0;
    else c = min((r - tree[v].mindel2)/2, r - tree[v].raz);

    if(l == r) return c;
    int mid = (l+r)/2;
    if(qr <= mid) return min(c,query(v*2+0,l,mid+0));
    else return min(c,query(v*2+1,mid+1,r));
}
void solve()
{
    for(int i = 0; i <= 2*n+2; i++) dul[i] = 1e9;

    int brl = 0, br = 0, brr = n;
    ///cout << "tuka1" << endl;
    for(int point = 1; point <= 2*n; point++)
    {
        ///cout << "f1" << endl;
        br += st[point];
        brr -= st[point];

        ql = 0, qr = br, val = {1,0};
        if(ql <= qr) update(1,0,2*n);
        ///cout << "f2" << endl;
        ql = br+1, qr = br + 2*min(brl,brr), val = {2,br-1};
        if(ql <= qr) update(1,0,2*n);
        ///cout << "f3" << endl;
        ql = br + 2*min(brl,brr) + 1, qr = 2*n, val = {3,br + min(brl,brr)};
        if(ql <= qr) update(1,0,2*n);
        //for(int i = br; i >= 0; i--) dul[i] = 0;
        //for(int i = 1; i <= min(brl,brr); i++) dul[br + 2*i] = min(dul[br + 2*i], 0 + i);
        //for(int i = 1; i <= abs(brr-brl); i++) dul[br + 2*min(brl,brr) + i] = min(dul[br + 2*min(brl,brr) + i], 0 + min(brl,brr) + i);
        ///cout << "f4" << endl;
        brl += fn[point];
        br -= fn[point];
    }
    ///cout << "tuka?" << endl;
    int old = 1e9;
    for(int i = 2*n; i >= 1; i--)
    {
        ql = i;
        qr = i;
        dul[i] = min(old,query(1,0,2*n));
    }
    int k;
    for(int i = 1; i <= q; i++)
    {
        cin >> k;
        cout << dul[k]<< " ";
    }
    cout << endl;
}

int main()
{
    read();
    solve();
    return 0;
}
