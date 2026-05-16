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

void read()
{
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
    {
        cin >> p[i].first >> p[i].second;
    }
    compress();
}

int dul[MAXN];
//long long dp[MAXN][MAXN];
void solve()
{
    for(int i = 0; i <= 2*n+2; i++) dul[i] = 1e9;

    for(int point = 1; point <= 2*n; point++)
    {
        int brl = 0, br = 0, brr = 0;
        for(int i = 1; i <= n; i++)
        {
            if(p[i].second < point) brl++;
            else if(point < p[i].first) brr++;
            else br++;
        }
        for(int i = br; i >= 0; i--) dul[i] = 0;
        for(int i = 1; i <= min(brl,brr); i++) dul[br + 2*i] = min(dul[br + 2*i], 0 + i);
        for(int i = 1; i <= abs(brr-brl); i++) dul[br + 2*min(brl,brr) + i] = min(dul[br + 2*min(brl,brr) + i], 0 + min(brl,brr) + i);
    }
    for(int i = 2*n; i >= 1; i--) dul[i] = min(dul[i+1],dul[i]);
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
