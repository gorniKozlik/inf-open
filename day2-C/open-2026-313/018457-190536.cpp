#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <numbers>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <climits>
#include <bit>
#include <random>
using namespace std;
using ll = long long;
using db = double;


mt19937 rnd(14);


int main() {
    cin.tie(0);
    iostream::sync_with_stdio(false);

    int tt = 1;
    while (tt--) {

    ll T, n, m, k, x;
    T = 3;
    n = 2;
    m = 1000;
    cin >> T >> n >> m;

    vector<ll> dp(n + 1, LLONG_MIN);
    vector<pair<ll, ll>> a(n);
    map<ll, bool> mp;
    for (int i = 0; i < n; i++) {
        // a[i].first = (rnd() % m) + 1;
        cin >> a[i].first;
        a[i].first--;
        a[i].second = i;
    }
    string s;
    
    // s = "LR";
    cin >> s;
    sort(a.begin(), a.end());

    vector<ll> b;
    bool ok = true;
    for (int i = 0; i < n; i++) {
        ll x = a[i].first;
        bool direction = s[a[i].second] == 'R';
        if (x == 0) {
            direction = true;
        } else if (x == m - 1) {
            direction = false;
        }
        if (!direction) x = m + m - x - 2;
        b.push_back(x);
        if (mp[(x + 1) % 2]) {
            ok = false;
            cout << "No\n";
            break;
            // return 0;
        }
        mp[x % 2] = true;
    }
    if (!ok) continue;
    cout << "Yes\n";

    if (T == 1) return 0;

    sort(b.begin(), b.end());
    b.resize(unique(b.begin(), b.end()) - b.begin());

    ll res = 0;
    ll mxdiff = 0;
    ll mxi = 0;
    ll last = -1;
    for (int i = 0; i < b.size(); i++) {
        x = b[i];
        if (last != -1) {
            ll diff = x - last;
            if (diff > mxdiff) {
                mxdiff = diff;
                mxi = i - 1;
            }
        }
        last = x;
    }
    ll diff = (2 * (m - 1) - last + b[0]);
    if (diff > mxdiff) {
        mxdiff = diff;
        mxi = b.size() - 1;
    }
    cout << mxdiff / 2 + 1 << '\n';

    if (T == 2) return 0;

    cout << b.size() - 1 << '\n';
    ll df = -1;
    ll b0 = b[b.size() - 2];
    ll b1 = b.back();
    while (df == -1) {
        if (b0 <= m - 2 && b1 > m - 2) {
            ll b11 = m - (b1 - m + 1) - 1;
            if (b0 <= b11) {
                df = (b11 - b0) / 2;
                continue;
            }
        }

        ll diff = b1 - b0;
        ll jmp = 0;
        ll target = 2 * (m - 1) / 2 + diff / 2;
        if (b1 <= target) {
            jmp = target - b1;
        } else {
            jmp = target + (2 * m - 2 - b1);
        }

        df = jmp;
    }

    if (n == 2) {
        ll diff = 2 * m - 2 - 2 * (mxdiff / 2 + 1);
        ll jmp = 0;
        ll target = 2 * (m - 1) / 2 + diff / 2;
        if (b1 <= target) {
            jmp = target - b1;
        } else {
            jmp = target + (2 * m - 2 - b1);
        }

        int i = 0;
        cout << jmp << ' ' << mxdiff / 2 + 1;
        continue;
    }

    ll cur = df;
    ll cur_m = m;
    bool aligned = true;
    for (int i = b.size() - 2; i >= -1; i--) {
        if (i == -1) i = b.size() - 1;
        ll diff = 0;
        if (i == b.size() - 1) {
            diff = (2 * (m - 1) - last + b[0]);
        } else {
            diff = b[i + 1] - b[i];
        }

        if (i == mxi) {
            if (i == b.size() - 2) continue;
            cur += diff;
            aligned = true;
            if (i == b.size() - 1) break;
            continue;
        }

        cur_m -= diff / 2;
        cur += (diff / 2) * (!aligned);
        aligned = false;
        if (n == 2) {
            ll b0 = (b[0] + cur) % (2 * m - 2);
            ll b1 = (b[1] + cur) % (2 * m - 2);

            if (b0 != (m - (b1 - m + 1) - 1)) {
                cout << b[0] << ' ' << b[1] << ' ' << m << ' ';
                cout << b[0] << ' ' << b[1] << ' ' << m << ' ';
                cout << b[0] << ' ' << b[1] << ' ' << m << ' ';
                cout << b[0] << ' ' << b[1] << ' ' << m << ' ';
                cout << b[0] << ' ' << b[1] << ' ' << m << ' ';
                cout << b[0] << ' ' << b[1] << ' ' << m << ' ';
                cout << b[0] << ' ' << b[1] << ' ' << m << ' ';
                cout << b[0] << ' ' << b[1] << ' ' << m << ' ' << a[0].first << ' ' << a[1].first;
                exit(1);
            }
        }
        cout << cur << ' ' << cur_m << '\n';


        if (i == b.size() - 1) break;
    }

    }
}
