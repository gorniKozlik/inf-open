#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#pragma GCC optimize("O3" , "Ofast" , "unroll-loops" , "fast-math")

#define endl '\n'
#define X first
#define Y second
#define MOD 1000000007

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector <int> vi;
typedef vector <long long> vll;
typedef vector <unsigned long long> vull;
typedef vector <string> vs;
typedef pair <int, int> pii;

void speed()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}


const int maxn = 2e5 + 7;
int n, q;
int k[maxn];
struct line
{
    int l, r;
};
line p[maxn];
bool cmp(line a, line b)
{
    if(a.l < b.l)return 1;
    else if(a.l == b.l)
    {
        if(a.r < b.r)return 1;
        else return 0;
    }
    else return 0;
}
void read_solve()
{
    cin >> n >> q;
    for(int i = 1;i <= n;i++)
    {
        cin >> p[i].l >> p[i].r;
    }
    for(int i = 1;i <= n;i++)
    {
        cin >> k[i];
    }
    int ans = 0;
    sort(p + 1, p + n + 1, cmp);
    deque <line> d;
    for(int i = 1;i <= n;i++)
    {
        d.push_back(p[i]);
    }
    while(!d.empty())
    {
        if(d.front().r < d.back().l)
        {
            ans++;
            d.pop_front();
            if(!d.empty())d.pop_back();
        }
        else d.pop_back();
    }
    cout << ans << endl;
}

int main()
{
    speed();
    read_solve();
    return 0;
}
