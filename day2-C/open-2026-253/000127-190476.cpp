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

        cout<<(k-1)*k/2<<" ";
    }
    cout<<endl;
    return 0;
}
