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
    for (int i = 0; i < n; i++) {
        ll l, r;
        v[i] = {l, r};
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        if (k == n) {
            cout << n / 2 << " ";
        } else {
            cout << k / 2 << " ";
        }
    }
    return 0;
}
