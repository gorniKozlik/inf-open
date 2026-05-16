#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll M = 998244353;

int check(int x, vector<int> l, vector<int> r) {
    int n = (int)l.size();
    vector<int> l1, l2, r1, r2;
    for (int i = 0; i < x; i++) {
        l2.push_back(r[i]);
        r2.push_back(l[n - 1 - i]);
    }
    for (int i = x; i < n; i++) {
        l1.push_back(l[n - 1 - i]);
        r1.push_back(r[i]);
    }
    l.erase(l.begin(), l.end());
    r.erase(r.begin(), r.end());
    int k1 = 0, k2 = 0;
    while (k1 < (int)l1.size() && k2 < (int)l2.size()) {
        if (l1[k1] < l2[k2]) {
            l.push_back(l1[k1]);
            k1++;
        } else {
            l.push_back(l2[k2]);
            k2++;
        }
    }
    while (k1 < (int)l1.size()) {
        l.push_back(l1[k1]);
        k1++;
    }
    while (k2 < (int)l2.size()) {
        l.push_back(l2[k2]);
        k2++;
    }

    k1 = 0, k2 = 0;
    while (k1 < (int)r1.size() && k2 < (int)r2.size()) {
        if (r1[k1] < r2[k2]) {
            r.push_back(r1[k1]);
            k1++;
        } else {
            r.push_back(r2[k2]);
            k2++;
        }
    }
    while (k1 < (int)r1.size()) {
        r.push_back(r1[k1]);
        k1++;
    }
    while (k2 < (int)r2.size()) {
        r.push_back(r2[k2]);
        k2++;
    }

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
