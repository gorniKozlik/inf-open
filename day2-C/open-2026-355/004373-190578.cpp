#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <iomanip>
#include <set>
#include <cstring>
#define control cout<<"e ne"<<endl;
#define endl '\n'
using namespace std;
int n,q,l,r,k;
void speed()
{
 ios_base::sync_with_stdio(false);
 cin.tie(0);
}
signed main()
{
    /*
    #ifdef ONLINE_JUDGE
    freopen("txt.in","r",stdin)
    freopen("txt.out","w",stdout)
    #endif
    */
    speed();
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>l>>r;
    while(q--)
    {
        cin>>k;
        cout<<max(1,k-1)<<endl;
    }
    return 0;
}
