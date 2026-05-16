/**
low cortisol default code
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#define maxn 400005
#define maxlog 21
#define PB push_back
#define X first
#define Y second
#define control std::cout<<"passed"<<"\n";


typedef long long ll;
typedef long double ld;
typedef std::pair <int , int> pii;
typedef std::pair <ll , ll> pll;


int l[maxn] , r[maxn];
int d[maxn];
int pref[maxn];
int table[maxlog][maxn];

int log2[maxn];

int query(int l , int r)
{
    int len = r - l + 1;
    return std::max(table[log2[len]][l] , table[log2[len]][r - (1 << log2[len]) + 1]);
}

void read()
{
    log2[1] = 0;
    for (int i = 2; i < maxn; i++)
        log2[i] = log2[i / 2] + 1;


    int n , q;
    std::cin >> n >> q;

    std::vector <int> comp;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> l[i] >> r[i];
        comp.PB(l[i]);
        comp.PB(r[i]);
    }

    std::sort(comp.begin(), comp.end());
    comp.erase(std::unique(comp.begin(), comp.end()), comp.end());

    std::map <int , int> id;
    for (int i = 0; i < comp.size(); i++)
        id[comp[i]] = i + 1;

    for (int i = 1; i <= n; i++)
        l[i] = id[l[i]] , r[i] = id[r[i]];

    for (int i = 1; i <= n; i++)
    {
        d[l[i]]++;
        d[r[i]]--;
    }
    for (int i = 1; i <= 2 * n; i++)
        pref[i] = pref[i - 1] + d[i];

    for (int i = 1; i <= 2 * n; i++)
        table[0][i] = pref[i];
    for (int power = 1; power < maxlog; power++)
        for (int i = 1; i + (power - 1) <= 2 * n; i++)
            table[power][i] = std::max(table[power - 1][i] , table[power - 1][i + (1 << (power - 1))]);

    while (q--)
    {
        int x;
        std::cin >> x;

        int maxx = query(x , 2 * n - x);

        /**int pom = 0;
        for (int i = x; i <= 2 * n - x; i++)
            pom = std::max(pom , pref[i]);*/


        std::cout << (std::max(0 , x - maxx) + 1) / 2 /** << " " << (std::max(0 , x - pom) + 1) / 2*/ << " ";
    }
    
    std::cout << "\n";
}




int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tests = 1;
    //std::cin >> tests;

    while (tests--)
    {
        read();
    }

    return 0;
}