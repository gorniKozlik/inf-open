#include <ios>
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct str {
    ll l, r;
};
int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector <str> v(n);
    vector <pair <int, int>> p;
    vector <pair<int, int>> m;
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        v[i] = {l, r};
        m.push_back({l, 1});
        m.push_back({r, -1});
    }
    sort(m.begin(), m.end());
    int sum = 0;
    for (int i = 0; i < n * 2 - 1; i++) {
        sum += m[i].second;
        p.push_back({min(i + 1, n * 2 - i - 1), sum});
    }
    sort(p.begin(), p.end());
    vector <int> ans(n + 1);
    int mx = 0;
    int ind = n * 2 - 2;
    for (int i = n; i >= 1; i--) {
        while (ind > -1 && p[ind].first == i) {
            mx = max(p[ind].second , mx);
            p.pop_back();
            ind--;
        }
        //cout << mx << endl;
        ans[i] = max(0, (i - mx + 1) / 2);
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
    return 0;
}
