#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;
const int N = 2e5 + 5;

int ans[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    int lp = 0, rp = n, in = 0;
    vector<pair<int, int>> event;
    for (int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        event.push_back({l, 0});
        event.push_back({r + 1, 1});
        event.push_back({r, 2});
    }

    sort(event.begin(), event.end());

    for (int i = 1; i <= n; ++i) {
        ans[i] = inf;
    }

    int mx_in = 0;
    vector<pair<int, int>> tmp;
    {
        int lp = 0, in = 0, rp = n;
        for (auto& [x, y]: event) {
            if (y == 0) --rp, ++in;
            else if (y == 1) ++lp, --in;
            else {
                mx_in = max(mx_in, in);
                tmp.push_back({in + 2 * min(lp, rp), x});
            }
            
        }
    }

    sort(tmp.rbegin(), tmp.rend());
    
    set<int> st;
    for (int i = 0; i < min(2500, (int)tmp.size()); ++i) {
        st.insert(tmp[i].second);
    }

    for (auto& [x, y]: event) {
        if (y == 0) --rp, ++in;
        else if (y == 1) ++lp, --in;
        else {
            if (!st.count(x)) continue;

            for (int i = 1; i <= in; ++i) {
                ans[i] = 0;
            }
    
            int delta = min(lp, rp);
            int qlp = lp, qrp = rp;
    
            int to = in + 2 * delta;
            for (int i = in + 1; i <= to; i += 2) {
                ans[i] = min(ans[i], (i - in + 1) / 2);
                ans[i + 1] = min(ans[i + 1], (i - in + 1) / 2);
            }
    
            qlp -= delta, qrp -= delta;
            for (int i = to + 1; i <= n; ++i) {
                ans[i] = min(ans[i], delta + (i - to));
            }
        }
    }

    while (q--) {
        int x; cin >> x;

        if (x <= mx_in) cout << 0 << " ";
        else cout << ans[x] << " ";
    }

    return 0;
}
