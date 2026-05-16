#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
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
    int middle = n - 1;
    int cntleft = 0, cntright = 0;
    for (auto [l, r] : a) {
        if (r <= middle) ++cntleft;
        if (l > middle) ++cntright;
    }
    for (int i = 0; i < q; ++i) cout <<cntleft<<' ';




}