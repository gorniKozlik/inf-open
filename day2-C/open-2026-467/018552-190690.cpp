#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using ll = long long;
using ld = long double;

const int MAXN = 3e5+50;
const int MOD = 998244353;
const int INF = 1e9;
const ll LLINF = 1e16;
const ld EPS = 1e-9;
const int LOGN = 22;
mt19937_64 rng();

ll binpow(ll x, ll k) {
    if (k == 0) return 1;
    if (k % 2 == 0) {
        ll d = binpow(x, k/2) % MOD;
        return d*d%MOD;
    }
    return x*(binpow(x, k-1))%MOD;
}

int n, q;
vector<int> coords;
vector<pair<int, int>> v;
vector<int> k;

struct Point {
    int x;
    int type = 0; // -1 = start ; 1 = end
};
vector<Point> points;

int cnt[MAXN], pref[MAXN], suf[MAXN];
int ans[MAXN];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    // ---Входные данные---
    cin >> n >> q;
    v.resize(n+1); k.resize(q+1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i].first >> v[i].second; v[i].second++;
        coords.push_back(v[i].first);
        coords.push_back(v[i].second);
    }
    for (int i = 1; i <= q; i++) cin >> k[i];

    // ---Сжатие координат---
    sort(coords.begin(), coords.end());
    unordered_map<int, int> mp;
    for (int i = 0; i < (int)coords.size(); i++) {
        mp[coords[i]] = (int)mp.size();
    }
    for (int i = 1; i <= n; i++) {
        v[i].first = mp[v[i].first];
        v[i].second = mp[v[i].second];
        points.push_back({v[i].first, -1});
        points.push_back({v[i].second, 1});
    }
    sort(points.begin(), points.end(), [](Point p1, Point p2){
        return p1.x < p2.x;
    });

    // Считаем массив # отрезков в точке + максимум
    int mx = 0, id = 0;
    suf[0] = n;
    for (Point p : points) {
        // cout << p.x << ' ' << p.type << '\n';

        if (p.x != 0) { // init
            cnt[p.x] = cnt[p.x-1];
            pref[p.x] = pref[p.x-1];
            suf[p.x] = suf[p.x-1];
        }
        if (p.type == -1) {
            cnt[p.x]++; suf[p.x]--;
            if (cnt[p.x] > mx) {
                mx = cnt[p.x];
                id = p.x;
            }
        }
        if (p.type == 1) {
            cnt[p.x]--; pref[p.x]++;
        }

        if (cnt[p.x] == mx) {
            if (abs(suf[id]-pref[id]) > abs(suf[p.x]-pref[p.x])) {
                id = p.x;
            }
        }
    }

    // ---Debug---
    /*
    cout << id << '\n';
    cout << cnt[id] << ' ' << pref[id] << ' ' << suf[id] << '\n';
    */

    for (int i = 0; i <= mx; i++) {
        ans[i] = 0;
    }

    int t = 0;
    int km = *max_element(k.begin()+1, k.end());
    for (int i = mx+1; i <= km;) {
        if (pref[id] && suf[id]) {
            pref[id]--; suf[id]--;
            ans[i] = ++t;
            ans[i+1] = t;
            i += 2;
            continue;
        }
        else if (pref[id]) {
            pref[id]--;
            ans[i] = ++t;
            i++;
            continue;
        }
        else if (suf[id]) {
            suf[id]--;
            ans[i] = ++t;
            i++;
            continue;
        }
        else i++;
    }

    for (int i = 1; i <= q; i++) {
        cout << ans[k[i]] << ' ';
    }
}
