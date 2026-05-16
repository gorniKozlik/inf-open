//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;
#define int long long
//#pragma GCC optimize("Ofast")
const int INF = 1e18;
const int mod = 998244353;
int binup(int a,int b) {
    if (!b)return 1;
    if (b % 2 == 0) {
        int mid = binup(a, b / 2);
        return (mid * mid) % mod;
    }
    return (a * binup(a, b - 1)) % mod;
}
int obr(int x) {
    return binup(x,mod-2);
}
void upd(vector <pair<int,int>> &vec,vector <int> &ans,int x) {
    int cnt1 = 0;
    int cnt2 = 0;
    int cnt3 = 0;
    int cnt4 = 0;
    int cnt5 = 0;
    for (auto el : vec) {
        if ( el.second < x) {
            cnt1++;
        }else if (el.first > x) {
            cnt2++;
        }else if (el.first == x) {
            cnt3++;
        }else if (el.second == x) {
            cnt4++;
        }else {
            cnt5++;
        }
    }
    if (cnt3) {
        cnt5++;
    }
    if (cnt4) {
        cnt5++;
    }
    if (cnt5) {
        ans[cnt5-1] = 0;
    }
    cnt5--;
    int cost_now = 0;
    while (1) {
        if (cnt1 && cnt2) {
            cnt5+=2;
            cost_now++;
            ans[cnt5]  = min(ans[cnt5],cost_now);
            cnt1--;
            cnt2--;
        }else if (cnt1 && cnt3) {
            cnt1--;
            cnt3--;
            cnt5+=1;
            cost_now++;
            ans[cnt5]  = min(ans[cnt5],cost_now);
        }else if (cnt2 && cnt4) {
            cnt2--;
            cnt4--;
            cnt5+=1;
            cost_now++;
            ans[cnt5]  = min(ans[cnt5],cost_now);
        }else {
            break;
        }
    }
}
signed main() {
    int n,q;
    cin >> n >> q;
    vector <pair<int,int>> vec(n);
    vector <int> all_dot;
    for (int i = 0;i < n;i++) {
        cin >>vec[i].first >> vec[i].second;
        all_dot.push_back(vec[i].first);
        all_dot.push_back(vec[i].second);
    }
    sort(all_dot.begin(),all_dot.end());
    vector <int> ans(n,INF);
    upd(vec,ans,all_dot[n-1]);
    for (int i = n - 2;i >= 0;i--) {
        ans[i] = min(ans[i],ans[i+1]);
    }
    vector <int> zap(q);
    for (int i = 0;i < q;i++) {
        cin >> zap[i];
        zap[i]--;
    }
    for (auto el : zap) {
        cout << ans[el] << " ";
    }

}
