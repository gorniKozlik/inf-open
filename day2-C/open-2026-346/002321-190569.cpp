#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 5;

struct El {
    int l, r;
};

struct Ev {
    int x, t;
};

bool cmp(Ev &a, Ev &b) {
    return a.x < b.x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<Ev> a;
    vector<El> b;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        a.push_back({l, 0});
        a.push_back({r, 1});
        b.push_back({l, r});
    }
    sort(a.begin(), a.end(), cmp);
    vector<int> ans(n + 1, INF);
    ans[1] = 0;
    for (int i = 2; i <= n; i++) {
        int cnt = 0, cnt2 = n, cnt3 = 0;
        for (int j = 0; j < a.size(); j++) {
            if (a[j].t == 0) {
                cnt2--;
                cnt3++;
            } else {
                cnt3--;
                cnt++;
            }
            if (cnt3 >= i) {
                ans[i] = 0;
                continue;
            }
            if ((i - cnt3 + 1) / 2 <= min(cnt, cnt2)) {
                ans[i] = min(ans[i], (i - cnt3 + 1) / 2);
            } else {
                continue;
            }
        }
    }
    while (q--) {
        int k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}
