#include<iostream>
#include<algorithm>
#include<set>
#pragma GCC optimize("Ofast")
using namespace std;

using ll = long long;
using ld = long double;

const ll infl = (ll)4e18 + 100;
const int infi = (int)1e9 + 100;
const int maxn = (int)1e6 + 10;
const int mod = (int)1e9 + 7;

int n, q;
pair<int, int> a[maxn];
pair<int, int> sl[maxn];
pair<int, int> sr[maxn];
int ans[maxn];
set<pair<int, int>> st;

inline bool cmp(pair<int, int> sr1, pair<int, int> sr2) {
    if (sr1.second != sr2.second)
        return sr1.second > sr2.second;
    return sr1.first > sr2.first;
}

inline int get() {
    int k = 0, mx_k = 0;
    for (auto& p : st) {
        if (p.second == 1)
            ++k;

        mx_k = max(k, mx_k);

        if (p.second == 2)
            --k;
    }

    return mx_k;
}

inline void solve() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        sl[i] = a[i]; sr[i] = a[i];
        st.insert({ a[i].first, 1 });
        st.insert({ a[i].second, 2 });
    }

    sort(sl, sl + n);
    sort(sr, sr + n, cmp);

    int nw = get() + 1;

    int l = 0, r = 0;
    while (nw <= n) {
        st.erase({ sl[l].second, 2 });
        st.erase({ sr[r].first, 1 });

        st.insert({ sl[l].second, 1 });
        st.insert({ sr[r].first, 2 });

        ++l; ++r;

        int nxt = get() + 1;
        for (int i = nw; i < nxt; ++i)
            ans[i] = ans[nw - 1] + 1;
        
        if (nw == nxt)
            break;
        
        nw = nxt;
    }

    while (q--) {
        int ki; cin >> ki;
        cout << ans[ki] << " ";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t_ = 1; // cin >> t_;
    while (t_--) {
        solve();
        cout << '\n';
    }

    return 0;
}