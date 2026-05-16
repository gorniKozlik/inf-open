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
    vector<ll> prefl;
    vector<ll> prefr;
    for (int i = 0;i<n;i++) {
        cin >>a >> b;
        arr.push_back({a,b});
        prefl.push_back(a);
        prefr.push_back(b);
    }
    sort(prefl.begin(),prefl.end());
    sort(prefr.begin(),prefr.end());
    vector<ll> res(n+1,inf);
    vector<pair<ll,ll>> ans;
    for (int tr = 0;tr<n;tr++) {
        cnt1 = 0;
        cnt2 = 0;
        cntMax = 0;
        cnt = 0;
        int ind = arr[tr].first;
        cnt1 = (lower_bound(prefr.begin(),prefr.end(),ind) - prefr.begin());
        cnt2 = n - (upper_bound(prefl.begin(),prefl.end(),ind) - prefl.begin());
        cntMax = n - cnt1 - cnt2;
        ans.push_back({cntMax,min(cnt1,cnt2)});
    }
    sort(ans.rbegin(),ans.rend());
    for (int i = 0;i<n;i++) {
        ll l = 0;
        ll r = n + 1;
        while (r - l > 1) {
            ll m = (l + r) / 2;
            ll x;
            if (m <= ans[i].first) {
                x = 0;
            }
            else if (m <= ans[i].first + ans[i].second * 2){
                x = (m - ans[i].first + 1) / 2;
            }
            else {
                x = (m - ans[i].first - ans[i].second);
            }
            if (res[m] >= x) {
                r = m;
            }
            else {
                l = m;
            }
        }
        for (int j = l + 1;j<=n;j++) {
            ll x;
            if (j <= ans[i].first) {
                x = 0;
            }
            else if (j <= ans[i].first + ans[i].second * 2){
                x = (j - ans[i].first + 1) / 2;
            }
            else {
                x = (j - ans[i].first - ans[i].second);
            }
            res[j] = x;
        }
    }
    for (int i = 0;i<q;i++) {
        cin >> a;
        cout << res[a] << " ";
    }
}
