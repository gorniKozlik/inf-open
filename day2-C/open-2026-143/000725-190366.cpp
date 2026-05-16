#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define endl "\n"
using ll = long long;
using pii = pair<int, int>;
using ld = long double;

template <typename t>
istream& operator>>(istream &in, vector<t> &a){
    for (auto &el : a){
        in >> el;
    }
    return in;
}

template <typename t>
ostream& operator<<(ostream &out, vector<t> &a){
    for (auto &el : a){
        out << el << " ";
    }
    return out;
}


struct event{
    int t, x;
};

bool cmp(event a, event b){
    if (a.x != b.x) return a.x < b.x;
    return a.t < b.t;
}


void solve(){
    int n, q;
    cin >> n >> q;
    vector<pii> a(n);
    vector<int> l(n), r(n);
    vector<event> events;
    for (int i = 0; i < n; ++i){
        cin >> l[i] >> r[i];
        a[i] = {l[i], r[i]};
        events.pb({0, l[i]});
        events.pb({1, r[i]});
    }
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    int cnt = 0;
    int start = 0, finish = 1e9 + 1;
    unordered_map<int, int> point;
    for (int i = 0; i < n; ++i){
        if (r[i] < l[n - i - 1]) {
            ++cnt;
            point[r[i]] = point[l[n - i - 1]] = 1;
        }
    }
    sort(events.begin(), events.end(), cmp);
    int now = 0;
    int ost = cnt;
    int can = 0;
    vector<pii> all;
    for (auto [t, x] : events){
        if (t == 0){
            all.pb({now, can});
            now++;
            if (point[x]) can--;
            all.pb({now, can});
        } else{
            all.pb({now, can});
            now--;
            if (point[x]) can++;
            all.pb({now, can});
        }
    }
    sort(all.begin(), all.end());
    vector<int> best(n + 1, -1);
    int mx = 0;
    for (auto [cnt, can] : all){
        best[cnt] = max(best[cnt], can);
        mx = max(mx, cnt);
    }
    vector<pii> st;
    int inf = 1e9 + 1;
    int nxt = 0;
    vector<int> ans(n + 1, inf);
    for (int i = 0; i <= mx; ++i){
        ans[i] = 0;
    }
    for (int i = 0; i <= n; ++i){
        while (!st.empty() && st.back().first + 2 * st.back().second < i) st.pop_back();
        if (best[i] != -1) st.pb({i, best[i]});
        if (i > mx && !st.empty()) ans[i] = (i - st.back().first + 1) / 2; 
    }
    for (int i = n - 1; i >= 0; --i){
        // assert(ans[i] <= ans[i + 1]);
    }
    while (q--){
        int k;
        cin >> k;
        cout << ans[k] << endl;
    }
}



signed main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    ios_base::sync_with_stdio(0); cin.tie(0);
#endif
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}