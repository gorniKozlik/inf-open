#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#pragma GCC target("avx2")

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

    int mx_in = 1;
    vector<int> arifm(n + 1, inf);
    vector<vector<pair<int, int>>> arifm_e(n + 3, vector<pair<int, int>>());
    vector<vector<pair<int, int>>> arifm_o(n + 3, vector<pair<int, int>>());
    
    for (auto& [x, y]: event) {
        if (y == 0) --rp, ++in;
        else if (y == 1) ++lp, --in;
        else {
            mx_in = max(mx_in, in);
    
            int delta = min(lp, rp);
            int to = in + 2 * delta;

            arifm[to + 1] = min(arifm[to + 1], delta - to);
            
            if (in & 1) {
                arifm_e[in + 1].push_back({-in, 1});
                arifm_e[in + 2 * delta + 1].push_back({-in, -1});

                arifm_o[in + 2].push_back({-in, 1});
                arifm_o[in + 2 * (delta + 1)].push_back({-in, -1});
            } else {
                arifm_o[in + 1].push_back({-in, 1});
                arifm_o[in + 2 * delta + 1].push_back({-in, -1});

                arifm_e[in + 2].push_back({-in, 1});
                arifm_e[in + 2 * (delta + 1)].push_back({-in, -1});        
            }

            // for (int i = in + 1; i <= to; i += 2) {
            //     ans[i] = min(ans[i], (i - in + 1) / 2);
            //     ans[i + 1] = min(ans[i + 1], (i - in + 1) / 2);
            // }
        }
    }

    {
        multiset<int> st;
        for (int i = 1; i <= n; i += 2) {
            for (auto& [x, y]: arifm_o[i]) {
                if (y > 0) st.insert(x);
                else st.erase(st.find(x));
            }

            ans[i] = min(ans[i], (i + *st.begin() + 1) / 2);
        }
        st.clear();
    }

    {
        multiset<int> st;
        for (int i = 2; i <= n; i += 2) {
            for (auto& [x, y]: arifm_e[i]) {
                if (y > 0) st.insert(x);
                else st.erase(st.find(x));
            }

            ans[i] = min(ans[i], (i + *st.begin() + 1) / 2);
        }
        st.clear();
    }

    int mn_arifm = inf;
    for (int i = 1; i <= n; ++i) {
        mn_arifm = min(mn_arifm, arifm[i]);
        ans[i] = min(ans[i], i + mn_arifm);
    }

    while (q--) {
        int x; cin >> x;

        if (x <= mx_in) cout << 0 << " ";
        else cout << ans[x] << " ";
    }

    return 0;
}
