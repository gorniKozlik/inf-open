#include<bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define debug(x) cout << "\n!debug " << (#x) << ": " << x << "\n";

struct pt {
    int start, end;
};

signed main() {
    int n, q;
    cin >> n >> q;
    vector<pt> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].start >> a[i].end;
    }
    while (q--) {
        int t; cin >> t;
        if (t <= 1) {
            cout << 0 << ' ';
        } else {
            int ans = t-1;
            cout << ans << ' ';
        }
    }
}