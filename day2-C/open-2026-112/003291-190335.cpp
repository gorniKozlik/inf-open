#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
const ll MAXN = 1e6 + 6;
const ll inf = 1e17 + 7;
const ll mod = 998244353;
const ll prod = 53;
mt19937 rnd(2);

int main() {
    ll n,q,a,b,cnt1,cnt2,cnt,cntMax;
    cin >> n >> q;
    vector<pair<ll,ll>> arr;
    for (int i = 0;i<n;i++) {
        cin >>a >> b;
        arr.push_back({a,b});
    }
    vector<ll> res(n+1,inf);
    for (int tr = 0;tr<n;tr++) {
        cnt1 = 0;
        cnt2 = 0;
        cntMax = 0;
        cnt = 0;
        int ind = arr[tr].first;
        for (int i = 0;i<n;i++) {
            if (arr[i].second < ind) {
                cnt1 ++;
            }
            else if (arr[i].first > ind) {
                cnt2 ++;
            }
            else {
                cntMax ++;
            }
        }
        for (int i = 1;i<=cntMax;i++) {
            res[i] = 0;
        }
        for (int i = cntMax + 1;i<=n;i++) {
            cnt ++;
            if (cnt1 > 0 && cnt2 > 0) {
                res[i] = cnt;
                i ++;
                res[i] = cnt;
                cnt1 --;
                cnt2 --;
            }
            else {
                res[i] = cnt;
            }
        }
    }
    for (int i = 0;i<q;i++) {
        cin >> a;
        cout << res[a] << " ";
    }
}
