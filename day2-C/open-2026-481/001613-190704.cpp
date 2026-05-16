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
    cout << "After compress" << endl;
    for(int i = 1; i <= n; i++) cout << p[i].first << " " << p[i].second << endl;
    //sort(p+1,p+n+1,cmp);
}

long long dul[MAXN];
void solve()
{
    for(int i = 0; i <= n; i++) dul[i] = 1e18;
    for(int l = 1; l <= 2*n; l++)
    {
        for(int r = l; r <= 2*n; r++)
        {
            vector<pair<int,int> >se;
            for(int i = 1; i <= n; i++)
            {
                if(l <= p[i].first && p[i].second <= r) se.push_back(p[i]);
            }
            sort(se.begin(),se.end(),cmpse);

            long long out = 0;
            for(int i = 0; i < se.size(); i++)
            {
                bool f = false;
                for(int j = 0; j < i; j++)
                {
                    if(se[j].second < se[i].second) f = true;
                }
                for(int j = i+1; j < se.size(); j++) if(se[i].second < se[j].second) f = true;
                out += f;
            }
            out = (out)/2;
            for(int i = 0; i <= se.size(); i++) dul[i] = min(dul[i],out);
        }
    }
    int k;
    for(int i = 1; i <= q; i++)
    {
        cin >> k;
        cout << dul[k] << " ";
    }
    cout << endl;
}

int main()
{
    read();
    solve();
    return 0;
}
