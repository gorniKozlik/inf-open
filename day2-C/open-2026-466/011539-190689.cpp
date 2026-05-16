#include<bits/stdc++.h>
using namespace std;

#define int long long
#define all(x) (x).begin(), (x).end()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
const char nl = '\n';

template<typename T>
istream &operator>> (istream& in, vector<T>& a) {
    for (auto &el : a) in >> el;
    return in;
}

template<typename T>
ostream& operator<< (ostream& out, vector<T> &a) {
    for (auto &el : a) out << el << ' ';
    return out;
}

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
}

void cmp(vector<pii>& a) {
    vector<int> s;
    for (auto el : a) {
        s.push_back(el.first);
        s.push_back(el.second);
    }
    sort(all(s));
    s.erase(unique(all(s)), s.end());
    for (auto &[f, q] : a) {
        f = lower_bound(all(s), f) - s.begin();
        q = lower_bound(all(s), q) - s.begin();
    }
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<pii> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i].first >> a[i].second;

    cmp(a);

    int m = 2 * n + 52;
    vector<int> st(m), fin(m);
    vector<int> pt;
    map<pii, int> mp;
    for (auto [f, s] : a) {
        mp[{f, s}] = 1;
        pt.push_back(f);
        pt.push_back(s);
    }

    sort(all(pt));
    pt.erase(unique(all(pt)), pt.end());

    for (auto [f, s] : a) {
        st[f]++;
        fin[s]++;
    }

    int sum_st = 0;
    int sum_fin = 0;
    for (int i = 2; i < m; i++) {
        sum_st += st[i];
    }

    //cout << st << nl;
    //cout << fin << nl;
    int ans = 1e18;
    for (int i = 1; i < (int)pt.size(); i++) {
        bool has = 0;
        int tmp1 = fin[pt[i - 1]], tmp2 = st[pt[i]];
        int cnt = min(fin[pt[i - 1]], st[pt[i]]);
        //cout << i << ' ' << sum_fin << ' ' << sum_st << nl;
        has = (cnt != 0);
        has |= mp[{pt[i - 1], pt[i]}];
        fin[pt[i - 1]] -= cnt;
        st[pt[i]] -= cnt;

        cnt += min(sum_fin, sum_st);
        int init_fin = sum_fin, init_st = sum_st;
        sum_fin -= cnt;
        sum_st -= cnt;

        if (sum_st == sum_fin) {
            //cout << i << ' ' << cnt << nl;
            ans = min(ans, cnt);
            fin[pt[i - 1]] = tmp1;
            st[pt[i]] = tmp2;
            sum_fin = init_fin;
            sum_st = init_st;
            sum_fin += fin[pt[i - 1]];
            if (i + 1 < pt.size())
                sum_st -= st[pt[i + 1]];
            continue;
        } else if (sum_fin == 0) {
            if (st[pt[i]] + has >= sum_st) {
                cnt += sum_st;
                ans = min(ans, cnt);
            }
        } else if (sum_st == 0) {
            if (fin[pt[i - 1]] + has >= sum_fin) {
                cnt += sum_fin;
                ans = min(ans, cnt);
            }
        }
        //cout << i << ' ' << cnt << nl;
        sum_fin = init_fin;
        sum_st = init_st;
        fin[pt[i - 1]] = tmp1;
        st[pt[i]] = tmp2;
        sum_fin += fin[pt[i - 1]];
        if (i + 1 < pt.size())
            sum_st -= st[pt[i + 1]];
    }

    vector<int> ks(q);
    cin >> ks;
    cout << ans;
}
