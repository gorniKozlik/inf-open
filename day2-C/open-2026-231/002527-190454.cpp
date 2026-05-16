#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define fi first
#define se second
#define print(x) f{or (auto &_: x) {cout <<_<<" ";}; cout<<"\n";

int mod = 998244353;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int,int> > a(n);
    vector<pair<int,int> > ev;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].fi >> a[i].se;
        ev.push_back({a[i].fi, i});
        ev.push_back({a[i].se, i});
    }


    sort(all(a));
    sort(all(ev));
    vector<int> cnt(n);
    int l = 0;
    int in = 0;
    vector<pair<int,int> > k;
    for (int i = 0; i < ev.size(); ++i) {
        int p = ev[i].fi;
        int j = ev[i].se;
        if (cnt[j] == 0) {
            in++;
            cnt[j]++;
        } else {
            in--;
            cnt[j]--;
            l++;
        }
        int r = n - l - in;

        int x = in;
        int y = in + 2 * (min(l, r));
        k.push_back({x, y});
    }


    vector<pair<int, pair<int,int> > > ev2;
    for (int i = 0; i < k.size(); ++i) {
        ev2.push_back({k[i].fi, {1, k[i].fi}});
        ev2.push_back({k[i].se + 1, {-1, k[i].fi}});
    }
    sort(all(ev2));

    map<int,int> lst;
    vector<int> ans(n + 1);
    int i = 0;
    int j = 0;
    while (i <= n) {
        while (j < ev2.size() && ev2[j].fi == i) {
            if (ev2[j].se.fi == -1) {
                lst[ev2[j].se.se]--;
                if (lst[ev2[j].se.se] == 0) {
                    lst.erase(ev2[j].se.se);
                }
            } else {
                lst[ev2[j].fi]++;
            }
            j++;
        }

        ans[i] = (i - (prev(lst.end())->fi) + 1) / 2;
        i++;
    }

    for (int d = 0; d < q; ++d) {
        int c;
        cin >> c;
        cout << ans[c] << " ";
    }
}


signed main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int _t = 1;
    //cin>>_t;
    while (_t--) {
        solve();
    }
    return 0;
}
