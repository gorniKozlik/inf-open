#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll M = 998244353;

int check(int x, vector<int> l, vector<int> r) {
    int n = (int)l.size();
    for (int i = 0; i < x; i++) {
        swap(r[i], l[n - 1 - i]);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    int bal = 0, mx = 0;
    int i = 0, j = 0;
    while (i < n && j < n) {
        if (l[i] < r[j]) {
            bal++;
            i++;
        } else {
            bal--;
            j++;
        }
        mx = max(mx, bal);
    }
    while (i < n) {
        bal++;
        i++;
        mx = max(mx, bal);
    }
    return mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> l, r;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        l.push_back(x);
        r.push_back(y);
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    while (q--) {
        int ask;
        cin >> ask;
        int ll = -1, rr = 0;
        while (rr < n && r[rr] < l[n - 1 - rr]) {
            rr++;
        }
        while (rr - ll > 1) {
            int mid = (ll + rr) / 2;
            if (check(mid, l, r) >= ask) {
                rr = mid;
            } else {
                ll = mid;
            }
        }
        cout << rr << '\n';
    }

}
