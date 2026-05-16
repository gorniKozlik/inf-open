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
int l[maxn];
int r[maxn];
int k[maxn];
void read_solve()
{
    cin >> n >> q;
    for(int i = 1;i <= n;i++)
    {
        cin >> l[i] >> r[i];
    }
    for(int i = 1;i <= n;i++)
    {
        cin >> k[i];
        cout << k[i] << " ";
    }
    cout << endl;
}

int main()
{
    speed();
    read_solve();
    return 0;
}
