#pragma GCC optimize("O3,unroll-loops")
#pragma  GCC target("avx,sse,sse2,sse3")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n,q;
    cin >> n >> q;
    vector<int> vctr;
    vector<pair<int,int>> vec(n);

    vector<int> left,right;

    for (int i=0;i<n;i++) {
        int x,y;
        cin >> x >> y;
        vctr.push_back(x);
        vctr.push_back(y);

        vec[i] = {x,y};
    }

    sort(vctr.begin(),vctr.end());
    map<int,int> mp;

    for (int i=0;i<n*2;i++) {
        mp[vctr[i]] = i;
    }

    for (int i=0;i<n;i++) {
        vec[i].first = mp[vec[i].first];
        vec[i].second = mp[vec[i].second];
    }

    // for (auto [l,r] : vec) {
    //     cout << l << ' ' << r << endl;
    // }cout << endl;


    vector<int> cnt(n*2,0);
    for (auto [l,r] : vec) {
        cnt[l]++;
        if (r + 1 < 2 * n) {
            cnt[r + 1]--;
        }

        left.push_back(l);
        right.push_back(r);
    }

    left.push_back(-1);right.push_back(-1);
    left.push_back(2*n);right.push_back(2*n);

    sort(left.begin(),left.end());
    sort(right.begin(),right.end());

    for (int i=1;i<2*n;i++) {
        cnt[i] += cnt[i-1];
    }

    // for (auto i : cnt) {
    //     cout << i << ' ';
    // }cout << endl;

    vector<int> ans(n+1,n+1);

    for (int i=0;i<2*n;i++) {
        ans[cnt[i]] = 0;

        int l1 = -1;
        int r1 = left.size()-1;
        while (r1-l1>1) {
            int m = (r1+l1)/2;
            if (left[m] > i) {
                r1 = m;
            }else {
                l1 = m;
            }
        }

        int l2 = 0;
        int r2 = right.size();
        while (r2-l2>1) {
            int m = (r2+l2)/2;
            if (right[m] < i) {
                l2 = m;
            }else {
                r2 = m;
            }
        }

        int cnt_l = l2;
        int cnt_r = left.size() - r1 - 1;

        // cout << i << ' ' << cnt_l << ' ' << cnt_r << endl;

        int k = min(cnt_l,cnt_r);
        for (int j=0;j<k;j++) {
            if (cnt[i] + 2 * j + 1 <= n) {
                ans[cnt[i] + 2 * j + 1] = min(ans[cnt[i]] + j + 1, ans[cnt[i] + 2 * j + 1]);
            }else {
                break;
            }
            if (cnt[i] + 2 * j + 2 <= n) {
                ans[cnt[i] + 2 * j + 2] = min(ans[cnt[i]] + j + 1,ans[cnt[i] + 2 * j + 2]);
            }
        }
        for (int j=cnt[i] + k*2 + 1;j<=n;j++) {
            ans[j] = min(ans[j], ans[cnt[i]] + k + (j - cnt[i] - k * 2));
        }
    }

    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout << fixed << setprecision(20);

    int TTT;
    // cin >> TTT;
    TTT = 1;

    while (TTT--) {
        solve();
    }
}