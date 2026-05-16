#include<bits/stdc++.h>
using namespace std;

unordered_map<long long, bool>m;

int main ()
{
    long long n, q;
    cin>>n>>q;

    vector<pair<long long, long long>>v;
    vector<long long>kol;

    for (long long i=0; i<n; i++)
    {
        long long x, y;
        cin>>x>>y;

        v.push_back({x, y});
        kol.push_back(x);
        kol.push_back(y);
    }

    sort(kol.begin(), kol.end());

    for (long long i=0; i<kol.size(); i++)
    {
        if (i<kol.size()/2)
        {
            m[kol[i]]=0;
        }
        else
        {
            m[kol[i]]=1;
        }
    }
    long long br=0;
    for (long long i=0; i<v.size(); i++)
    {
        if (m[v[i].first]==m[v[i].second])
        {
            br++;
        }
    }
    cout<<br/2<<endl;
    return 0;
}
