#pragma GCC optimize("O3,unroll-loops")
#include<vector>
#pragma GCC target("avx,avx2")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#ifdef DBG
#define $(x) x
#else
#define $(x)
#endif

#define debug(x) $(cout << #x << " = " << x << endl)

#define all(x) x.begin(), x.end()

constexpr int INF = 1e9 + 7;
constexpr ll LINF = 1e18 + 7;

void WA() {
    cout << "THIS IS WRONG ANSWER" << endl;
    exit(0);
}

void RE() {
    exit(1);
}

void TL() {
    unsigned x = 0;
    while (true) x++;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> p(n);
    vector<int> is;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first >> p[i].second;
        is.push_back(p[i].first);
        is.push_back(p[i].second);
    }

    sort(all(is));
    vector<int> a(2 * n, 0);
    for (int i = 0; i < n; ++i) {
        auto [s, e] = p[i];
        s = lower_bound(all(is), s) - is.begin();
        e = lower_bound(all(is), e) - is.begin();
        a[s] = 1;
        a[e] = -1;
    }

    int cnt = 0;
    multiset<int> s;
    vector<int> px(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        cnt += a[i];
        if (i + 1 < 2 * n) s.insert(cnt);
        px[i] = cnt;
    }

    int k = 0;
    int l = 0;
    int r = 2 * n - 1;
    vector<int> v(1, *s.rbegin());

    
    for (int _ = 0; _ < 2 * n; ++_) {        
        while (a[l] == 1) {
            s.erase(s.find(px[l]));
            l++;
        }
        while (a[r] == -1) {
            r--;
            s.erase(s.find(px[r]));
        }
        k += 2;
        v.push_back(max(max(l, 2 * n - r - 1), (s.size() ? *s.rbegin() + k : k)));
        a[l] = 1;
        a[r] = -1;
        if (v.back() == n) break;
        $(for (int i : s) cout << i << ' '; cout << endl;)
        debug(l << ' ' << r << ' ' << v.back());
    }

    vector<int> ans(n + 1, 0);
    int i = 0;
    for (int j = 0; j < v.size(); ++j) {
        for (; i <= v[j]; ++i) {
            ans[i] = j;
        }
    }

    for (int i = 0; i < m; ++i) {
        int q;
        cin >> q;
        cout << ans[q] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    $(cin >> t);
    while (t--) {
        debug("=-=-=-=-=-=-=-=");
        solve();
    }
}