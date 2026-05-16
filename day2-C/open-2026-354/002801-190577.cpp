#include <bits/stdc++.h>
#pragma ("O3")
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#define int long long
#define gcd(a,b) __gcd(a,b)
#define lcm(a,b) a / gcd(a,b) * b
#define MX LLONG_MAX
#define MN LLONG_MIN
#define sqr(x) (x) * (x)

using namespace std;
using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

const int N = 1e5 + 2;

int f[N];

void update(int i,int x)
{
    for(i = i + 1; i < N; i += (i & -i))
    {
        f[i] += x;
    }
}

int get(int i)
{
    int res = 0;
    for(i = i + 1; i < N; i -= (i & -i))
    {
        res += f[i];
    }
    return res;
}

const int mod = 998244353;

int binpow(int a,int b)
{
    int res = 1;
    while(b)
    {
        if(b & 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b>>=1;
    }
    return res;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
//    ifstream("input.txt");
//    ofstream("output.txt");

   int n,q;
   cin>>n>>q;
   vector<pair<int,int>>a(n);
   map<int,int>mp;
   for(int i =0;i<n;++i){
        cin>>a[i].first>>a[i].second;
        mp[a[i].first]++;
        mp[a[i].second]++;
   }
   vector<int>b(q);
   for(int i=0;i<q;++i){
    cin>>b[i];
   }

//   int num = 0;
//   unordered_map<int,int>nw;
//   for(auto to:mp){
//        nw[to.first] = num;
//        ++num;
//   }
//   vector<int>del(num + 1,0);
//   for(int i=0;i<n;++i){
//        del[nw[a[i].first]]++;
//        del[nw[a[i].second] + 1]--;
//   }
//   int sum = 0;
//   for(int i = 0;i <del.size();++i){
//        sum+=del[i];
//        del[i] = sum;
//   }
   for(int i=0;i<q;++i){
        cout<<b[i] / 2<<" ";
   }

}
