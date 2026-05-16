#ifndef LOCAL
#pragma GCC optimize("O3,unroll-loops")
#endif

#include <bits/extc++.h>

using namespace std;

#define int long long
#define ll long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()

int n, q;
vector<int> t;

void upd(int pos) {
    for (int i = pos; i <= 2 * n; i += i & (-i)) t[i]++;
}

int sum(int r) {
    int ans = 0;
    for (int i = r; i > 0; i -= i & (-i)) ans += t[i];
    return ans;
}

int sum(int l, int r) {
    return sum(r) - sum(l - 1);
}

int32_t main() {
#ifndef LOCAL
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
#endif
    cin >> n >> q;
    vector<pair<int,int> > a(n);
    t.resize(2 * n + 2);
    for (auto &[l,r]: a) cin >> l >> r;
    /*set <int> s;
    for (auto [l,r] : a) {
        s.insert(l);
        s.insert(r);
    }
    map <int,int> to;
    int pos = 1;
    for (int i : s) to[i] = pos++;
    for (auto &[l,r] : a) {
        l = to[l];
        r = to[r];
    }
    sort(all(a));*/
    set <int> sl, sr;
    for (auto [l,r] : a) {
        sl.insert(l);
        sr.insert(r);
    }
    int ans = 0;
    int minr = *sr.begin();
    int maxl = *(--sl.end());
    while (minr < maxl){
        sr.erase(sr.begin());
        sl.erase(--sl.end());
        minr = *sr.begin();
        maxl = *(--sl.end());
        ans++;
    }
    cout << ans;
    return 0;
}
