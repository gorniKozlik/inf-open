#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int INF = 1e9 + 7;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int>h;
    vector<pair<int, int>>a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        h.push_back(a[i].first);
        h.push_back(a[i].second);
    }
    sort(h.begin(), h.end());
    h.resize(unique(h.begin(), h.end()) - h.begin());
    for (auto &[l, r] : a) {
        l = lower_bound(h.begin(), h.end(), l) - h.begin();
        r = lower_bound(h.begin(), h.end(), r) - h.begin();
    }
    // int middle = n - 1;
    // int cntleft = 0, cntright = 0;
    // for (auto [l, r] : a) {
    //     if (r <= middle) ++cntleft;
    //     if (l > middle) ++cntright;
    // }
    // ans[n] = cntleft;
    vector<int>ans(n + 1, INF);
    vector<pair<int, int>>ev;
    for (int i =0 ; i < n; ++i) {
        ev.push_back({a[i].first , 1});
        ev.push_back({a[i].second, -1});
    }
    sort(ev.begin(), ev.end());
    int cntleft = 0, cntright = n;
    int ind = 0;
    for (auto [x, t] : ev) {
        if (t == 1) {
            --cntright;
        }
        else {
            ++cntleft;
        }
        ++ind;
        int els = n - cntleft - cntright;
        ans[min(ind, 2 * n - ind)] = min(ans[min(ind, 2 * n - ind)], (min(ind, 2 * n - ind) - els + 1) / 2);
    }
    for (int i = n - 1; i > 0; --i) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    for (auto x : ans) cout <<x<<' ';
    cout <<"\n";

}