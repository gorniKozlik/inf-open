#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define control std::cout<<"here"<<'\n';
const ll maxn = 2 * 1e5 + 5;
ll n, q, qu[maxn], ans[maxn];
std::vector<std::pair<ll, ll>> t;
void speed()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
}
void read()
{
    std::cin >> n >> q;
    ll l, r;
    for(ll i = 1; i <= n; i ++)
    {
        std::cin >> l >> r;
        t.push_back({l, 0});
        t.push_back({r, 1});
    }
    t.push_back({-1, -1});
    sort(t.begin(), t.end());
    for(ll i = 1; i <= q; i ++)
        {
            std::cin >> qu[i];
            ans[i] = 1e18;
        }
    ll curll = 0, lend = 0, rbeg = n;
    for(ll i = 1; i <= 2 * n; i ++)
    {
        if(t[i].ss == 0)
        {
            curll ++;
            rbeg --;
        }
        else
        {
            curll --;
            lend ++;
        }
        if(true)
        {
           // std::cout << curll << " " << lend << " " << rbeg << '\n';
            for(ll j = 1; j <= q; j ++)
            {

                if(curll >= qu[j])
                {
                    ans[j] = 0;
                    continue;
                }
                if((qu[j] - curll + 1) / 2 <= std::min (lend, rbeg))
                {
                    //if(qu[j] == 6) std::cout << "i: " << i << " " << curll << " " << lend << " " << rbeg << '\n';
                    ans[j] = std::min(ans[j], (qu[j] - curll + 1) / 2);
                }

            }
        }

    }
    for(ll i = 1; i <= q; i ++)
        std::cout << ans[i] << " ";
}
int main()
{
    speed();
    read();
    return 0;
}
