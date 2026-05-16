//#define _GLIBCXX_DEBUG
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

//#define int long long

using namespace std;
using ll = long long;
using ld = long double;

const int INTI = 2e9 + 5, MAXN = 1e5 + 1, MOD = 998244353;
const ll INF = 9e18 + 5;

struct node {
    int two, one, free;
};

bool cmp(node a, node b) {
    if (a.two != b.two)
        return a.two > b.two;
    return a.free > b.free;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int> > v;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        v.push_back({l, 0});
        v.push_back({r, 1});
    }
    sort(v.begin(), v.end());
    vector<node> a;
    int ch1 = n, ch2 = 0, chnow = 0;
    for (int i = 0; i < v.size(); ++i) {
        int fl = v[i].second;
        if (!fl) {
            ch1--;
            chnow++;
        } else {
            node nd;
            nd.free = chnow;
            nd.two = min(ch1, ch2) + chnow / 2;
            nd.one = max(ch1, ch2) - min(ch1, ch2);
            chnow--;
            ch2++;
            a.push_back(nd);
        }
    }
    sort(a.begin(), a.end(), cmp);
    reverse(a.begin(), a.end());
    n = a.size();
    while (q--) {
        int x;
        cin >> x;
        int mn = INFI;
        for (int i = 0; i < min(n, 3000); ++i) {
            int sum = min(a[i].two * 2, x);
            int need = max(0, (sum + 1 - a[i].free % 2) / 2 - a[i].free / 2);
            if (sum < x) {
                need += x - sum - a[i].free % 2;
            }
            mn = min(mn, need);
        }
        cout << mn << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while (t--)
        solve();
    return 0;
}
