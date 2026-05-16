#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <bitset>
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof pop_front
//#define int long long

using namespace std;
using ll = long long;
using ld = long double;

void sol() {
    int n, q;
    cin >> n >> q;
    vector<int> ans(n + 1);
    vector<int> l(n), r(n), xs;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        xs.pb(l[i]);
        xs.pb(r[i]);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    for (int &i : l) i = lower_bound(xs.begin(), xs.end(), i) - xs.begin();
    for (int &i : r) i = lower_bound(xs.begin(), xs.end(), i) - xs.begin();
    int k = xs.size();
    vector<int> beg(k), en(k);
    for (int i = 0; i < n; i++) {
        beg[l[i]]++;
        if (r[i] < k - 1) en[r[i] + 1]++;
    }
    int lef = 0, rig = n;
    vector<pair<int, int>> b;
    for (int i = 0; i < k; i++) {
        lef += en[i];
        b.pb({n - lef - rig, min(lef, rig)});
        rig -= beg[i];
    }
    sort(b.rbegin(), b.rend());
    int rr = 0;
    for (auto [x, c] : b) {
        for (int i = rr; i <= x + 2 * c; i++) {
            if (i <= x) ans[i] = 0;
            else ans[i] = (i - x + 1) / 2;
        }
        rr = max(rr, x + 2 * c + 1);
    }
    while (q--) {
        int qi;
        cin >> qi;
        cout << ans[qi] << ' ';
    }
    cout << '\n';
    return;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    sol();
    return 0;
}
