#include <bits/stdc++.h>

#pragma GCC optimization("Ofast")

#define int long long
#define all(a) a.begin(), a.end()
#define pii pair <int, int>
#define fr first
#define se second
#define uwu ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;

const int maxn = 1 << 20;
const int mod9 = 998244353;
const int mod7 = 1e9 + 7;

pii t[maxn];

void push(int v, int v1, int v2){
    t[v1].fr += t[v].se;
    t[v1].se += t[v].se;
    t[v2].fr += t[v].se;
    t[v2].se += t[v].se;
    t[v].se = 0;
}

void update(int v, int tl, int tr, int l, int r, int x){
    if (tl > r || tr < l){
        return;
    }
    if (l <= tl && tr <= r){
        t[v].fr += x;
        t[v].se += x;
        return;
    }
    push(v, v << 1, v << 1 | 1);
    int mid = (tl + tr) >> 1;
    update(v << 1, tl, mid, l, r, x);
    update(v << 1 | 1, mid + 1, tr, l, r, x);
    t[v].fr = max(t[v << 1].fr, t[v << 1 | 1].fr);
}

void solve(){
    int n, q;
    cin >> n >> q;
    vector <pii> s(n);
    vector <int> b(2 * n), answer(n + 1, 0);
    for (int i = 0; i < n; ++i){
        cin >> s[i].fr >> s[i].se;
        b[i] = s[i].fr;
        b[i + n] = s[i].se;
    }
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    int mx = 0;
    vector <int> a(q);
    for (int i = 0; i < q; ++i){
        cin >> a[i];
        mx = max(a[i], mx);
    }
    multiset <pii> st, st1;
    for (int i = 0; i < n; ++i){
        s[i].fr = lower_bound(all(b), s[i].fr) - b.begin();
        s[i].se = lower_bound(all(b), s[i].se) - b.begin();
        st.insert({s[i].se, s[i].fr});
        st1.insert({s[i].fr, s[i].se});
        update(1, 0, 2 * n, s[i].fr, s[i].se, 1);
    }
    int cnt = 0, cur = 0;
    while (cnt < mx){
        for (int i = cnt + 1; i <= t[1].fr; ++i){
            answer[i] = cur;
        }
        cnt = t[1].fr;
        ++cur;
        if (cnt >= mx){
            break;
        }
        pii p = *st.begin(), p1 = *(--st1.end());
        swap(p.fr, p.se);
        while (st.size() && p.fr == p1.fr && p.se == p1.se){
            st.erase(st.begin());
            st1.erase(--st1.end());
            p = *st.begin(), p1 = *(--st1.end());
            swap(p.fr, p.se);
        }
        p = *st.begin(), p1 = *(--st1.end());
        update(1, 0, 2 * n, p.se, p.fr, -1);
        update(1, 0, 2 * n, p1.fr, p1.se, -1);
        update(1, 0, 2 * n, p.se, p1.se, 1);
        update(1, 0, 2 * n, p.fr, p1.fr, 1);
        st.erase(st.begin());
        st1.erase(--st1.end());
        st.insert({p1.fr, p.fr});
        st1.insert({p.fr, p1.fr});
    }
    for (int i = 0; i < q; ++i){
        cout << answer[a[i]] << ' ';
    }
}

int32_t main(){

    int test = 1;
    //cin >> test;
    while (test--){
        solve();
    }
}
