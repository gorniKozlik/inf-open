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
    ll n,q,a,b;
    cin >> n >> q;
    vector<pair<ll,ll>> arr;
    vector<pair<ll,ll>> arr1;
    for (int i = 0;i<n;i++) {
        cin >>a >> b;
        arr.push_back({a,b});
        arr1.push_back({b,a});
    }
    sort(arr.begin(),arr.end());
    sort(arr1.begin(),arr1.end());
    vector<ll> res(n+1,inf);
    set<ll> ans;
    ll cnt = 0;
    ll cntMax = 0;
    ll ind = 0;
    for (auto u:arr){
        while (ans.size() > 0) {
            if ((*ans.begin()) < u.first) {
                ans.erase(ans.begin());
                cnt --;
            }
            else {
                break;
            }
        }
        cnt ++;
        ans.insert(u.second);
        if (cnt > cntMax) {
            cntMax = cnt;
            ind = *ans.begin();
        }
    }
    for (int i = 1;i<=cntMax;i++) {
        res[i] = 0;
    }
    ll cnt1 = 0;
    ll cnt2 = 0;
    for (int i = 0;i<n;i++) {
        if (arr[i].second < ind) {
            cnt1 ++;
        }
        else if (arr[i].first > ind) {
            cnt2 ++;
        }
    }
    cnt = 0;
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
    for (int i = 0;i<q;i++) {
        cin >> a;
        cout << res[a] << " ";
    }
}
