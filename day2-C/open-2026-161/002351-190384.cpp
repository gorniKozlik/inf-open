#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ll = long long;
#define int long long
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using namespace std;

template<typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
    return in >> a.first >> a.second;
}

template<typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &a) {
    return out << a.first << ' ' << a.second << '\n';
}

template<typename T>
istream &operator>>(istream &in, vector<T> &a) {
    for (auto &i: a)in >> i;
    return in;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &a) {
    for (auto &i: a)out << i << ' ';
    return out;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<vector<T> > &a) {
    for (auto &i: a)out << i << '\n';
    return out;
}

constexpr int mod = 998244353;
constexpr int inf = 1e18 + 7;

template<typename T>
T fast_pow(T a, int n) {
    if (n == 0)return 1;
    if (n % 2 == 1)return a * fast_pow(a, n - 1);
    T t = fast_pow(a, n / 2);
    return t * t;
}

struct Zm {
    int k;

    Zm(int k = {}) : k(k % mod) {
        if (this->k < 0)this->k += mod;
    }

    Zm operator+(const Zm &other) const {
        return {k + other.k};
    }

    Zm operator-(const Zm &other) const {
        return {k - other.k};
    }

    Zm operator*(const Zm &other) const {
        return {k * other.k};
    }
};

struct Line {
    int k;
    int b;

    Line(int k = {}, int b = {}) : k(k), b(b) {
    }

    int operator()(int x) const {
        return k * x + b;
    }
};

struct LiChao {
    vector<Line> d;
    vector<int> points;
    int n;

    LiChao(const vector<int> &x) {
        points = x;
        sort(points.begin(), points.end());
        points.resize(unique(points.begin(), points.end()) - points.begin());
        n = points.size();
        d.resize(4 * n, {0, inf});
    }

public:
    void add(Line l) {
        add(0, 0, n, l);
    }

    int get(int x) {
        int ind = lower_bound(points.begin(), points.end(), x) - points.begin();
        return get(0, 0, n, ind);
    }

private:
    void add(int t, int tl, int tr, Line l) {
        int tm = (tl + tr) / 2;
        if (d[t](points[tm]) > l(points[tm]))swap(l, d[t]);
        if (tl + 1 == tr)return;
        if (d[t].k == l.k)return;
        if (d[t].k < l.k) add(2 * t + 1, tl, tm, l);
        else add(2 * t + 2, tm, tr, l);
    }

    int get(int t, int tl, int tr, int ind) {
        if (tl + 1 == tr)return d[t](points[ind]);
        int tm = (tl + tr) / 2;
        if (tm <= ind)return min(d[t](points[ind]), get(2 * t + 2, tm, tr, ind));
        else return min(d[t](points[ind]), get(2 * t + 1, tl, tm, ind));
    }
};

struct Test {
    int n, q;
    vector<pair<int,int> > a;

    Test() {
        cin >> n>>q;
        a.resize(n);
        cin >> a;
        vector<int> b;
        for (auto [x,y]: a) {
            b.push_back(x);
            b.push_back(y);
        }
        sort(b.begin(), b.end());
        vector<int> starts;
        vector<int> ends;
        for (auto &[x,y]: a) {
            x = lower_bound(b.begin(), b.end(), x) - b.begin();
            y = lower_bound(b.begin(), b.end(), y) - b.begin();
            starts.push_back(x);
            ends.push_back(y);
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());
        vector<int> left(2 * n, 0);
        vector<int> right(2 * n, 0);
        {
            int now = 0;
            for (int i = 0; i < 2 * n - 1; i++) {
                while (now != n && ends[now] <= i) {
                    now++;
                }
                left[i] = now;
            }
        }
        {
            int now = 0;
            reverse(starts.begin(), starts.end());
            for (int i = 2 * n - 2; i >= 0; i--) {
                while (now != n && starts[now] > i) {
                    now++;
                }
                right[i] = now;
            }
        }
        vector<pair<int,int> > res(2 * n - 1);
        for (int i = 0; i < 2 * n - 1; i++) {
            res[i]={n-left[i]-right[i],min(left[i],right[i])};
        }
        sort(res.begin(), res.end());
        reverse(res.begin(), res.end());
        vector<int>ans(n+1);
        for (int i=0,now=0;i<=n;i++) {
            while (res[now].first+2*res[now].second<i) {
                now++;
                if (now==res.size()) {
                    now--;
                    break;
                }
            }
            ans[i]=max(0ll,(i-res[now].first+1)/2);
        }
        while (q--) {
            int k;
            cin>>k;
            cout<<ans[k]<<' ';
        }
    }
};

signed main() {
#ifdef home
    freopen(".in", "r",stdin);
    freopen(".out", "w",stdout);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        Test();
    }
}
