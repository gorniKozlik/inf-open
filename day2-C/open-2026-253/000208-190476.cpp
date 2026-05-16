#include<bits/stdc++.h>
using namespace std;
int main ()
{
    long long n, q;
    cin>>n>>q;

    vector<pair<long long, long long>>v;

    for (long long i=0; i<n; i++)
    {
        long long x, y;
        cin>>x>>y;

        v.push_back({x, y});
    }

    for (long long i=0; i<q; i++)
    {
        long long k;
        cin>>k;

        if (k<=3) cout<<k-1<<'\n';
        else
        {
            k-=3;
            cout<<2+k*2<<'\n';
        }
    }
    cout<<endl;
    return 0;
}
