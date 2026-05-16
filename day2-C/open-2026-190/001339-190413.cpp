#include <bits/stdc++.h>
#include  <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
#define all(x) x.begin(), x.end()
using ll = long long;
const int maxn = 8000000 + 10;
int h[maxn];
int maxint[maxn];
signed main()
{
#ifdef LOCAL
    freopen("main.in", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> rv(n);
    vector<int> lv(n);

    vector<int> pts;
    for (int i = 0; i < maxn; ++i) {
        h[i] = 1e9;
    }
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        pts.push_back(l);
        pts.push_back(r);
        lv[i] = l;
        rv[i] = r;
    }
    vector<int> sr = rv, sl = lv;
    sort(all(sr)); sort(all(sl));
sort(all(pts));
    for (int i = 0; i < pts.size() - 1; ++i) {

        int l = pts[i], r = pts[i+1];
        int fl = upper_bound(all(sr), l) - sr.begin();
        int fr = sl.end() - upper_bound(all(sl), r);
        // cout << l << " " << r << " " << fl << " " << fr << endl;
        int inter = n - fl - fr;
        // cout << "inter " << inter  << ": " << inter + 2 *  min(fl, fr)<< endl;
        h[inter] = 0;
        maxint[inter + 2 *min(fl, fr)] = max(maxint[inter + 2 *  min(fl, fr)], inter);
    }
    for (int i = maxn-2; i >= 0; --i) {
        h[i] = min(h[i+1], h[i]);
        int inr = maxint[i];
        int cur_val = (i  - inr + 1) / 2;
        // cout << maxint[i] << endl;
        if (i == 6) {
            // cout << maxint[i] << "!" << endl;
            // cout << cur_val << "aa " << endl;
        }
        if (inr > i) {
            continue;
        }
        h[i] = min(h[i],cur_val);
        if (i == 0) {
            continue;
        }
        maxint[i-1] = max(maxint[i-1], maxint[i]);
    }
    for (int i = 0; i < q; ++i) {
        int a;
        cin >> a;
        assert(h[a] >= 0 && h[a] < 1e9);
        cout << h[a] << " ";
    }



}