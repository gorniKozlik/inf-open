#include <bits/stdc++.h>
#define ll long long
#define int ll
#define all(x) x.begin(), x.end()
#define allr(x) x.rbegin(), x.rend()
#define uniq(x) x.erase(unique(all(x)), x.end())
#define fast_cin() cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0)

#pragma optimize("O3")
#pragma target("avx2")
using namespace std;

mt19937 rng(696969);

struct pa {
    int x;
    bool nac;
};

signed main() {
    fast_cin();
    int n,q; cin >> n >> q;
    vector<pair<int, int>> a(n);
    vector<pa> po;
    for (auto &i: a) {
        cin >> i.first >> i.second;
        po.push_back({i.first, true});
        po.push_back({i.second, false});
    }
    vector<int> k(q);
    for (int &i: k) cin >> i;

    sort(all(po), [](pa a, pa b) {
        return a.x < b.x;
    });

    vector<int> cnt(2*n);
    int now = 0;
    for (int i = 0; i < 2*n; ++i) {
        if (po[i].nac) ++now;
        cnt[i] = now;
        if (!po[i].nac) --now;
    }
    //i-cnt[i]+1
    for (int &j: k) {
        int mn = 1e9;
        for (int i = 0; i < 2*n; ++i) {
            if (cnt[i] >= j) {
                mn = 0;
                break;
            }
            int h = (j-cnt[i]), dl = (i-cnt[i]+1)/2,
            dr = n-cnt[i]-dl,
            da = min(dl, dr);
            if (da*2 >= h) {
                mn = min(mn, h/2);
            }
            else {
                if (po[i].nac && dl > dr)
                    if (da*2+1 >= h) mn = min(mn, da+1);
                if (!po[i].nac && dr > dl)
                    if (da*2+1 >= h) mn = min(mn, da+1);
            }
        }

        cout << mn << ' ';
    }
}
// 7 7
// 7 7
// 1 3
// 2 6
// 4 8
// 5 7
// 9 10
// 11 12
// 13 14
// 1 2 3 4 5 6 7