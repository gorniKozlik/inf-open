#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <string>
#include <cassert>

#define ll long long
#define ld long double
#define ull unsigned long long
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

using namespace std;

const int MAX = 2e9;
const int MIN = -2e9;
const int mod = 998244353;

int add(int a, int b) {
    a += b;
    if (a >= mod) {
        a -= mod;
    }
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) {
        a += mod;
    }
    return a;
}

int mul(int a, int b) {
    return (ll) a * b % mod;
}

int binpow(int a, ll k) {
    int res = 1;
    while (k) {
        if (k % 2) {
            res = mul(res, a);
        }
        a = mul(a, a);
        k /= 2;
    }
    return res;
}

struct segtree {
    struct node {
        int mx;
    };

    const node ZERO = {MIN};
    vector<node> t;
    int size;

    node merge(node a, node b) {
        node res;
        res.mx = max(a.mx, b.mx);
        return res;
    }

    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        t.assign(size * 2 - 1, ZERO);
    }

    void build(int v, vector<int> &a, int tl, int tr) {
        if (tr - tl == 1) {
            if (tl < a.size()) {
                t[v] = {a[tl]};
            }
            return;
        }
        int mid = (tl + tr) / 2;
        build(v * 2 + 1, a, tl, mid);
        build(v * 2 + 2, a, mid, tr);
        t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
    }

    void build(vector<int> &a) {
        init(a.size());
        build(0, a, 0, size);
    }

    node get(int v, int l, int r, int tl, int tr) {
        if (tr <= l or tl >= r) {
            return ZERO;
        }
        if (tl >= l and tr <= r) {
            return t[v];
        }
        int mid = (tl + tr) / 2;
        return merge(get(v * 2 + 1, l, r, tl, mid), get(v * 2 + 2, l, r, mid, tr));
    }

    int get(int l, int r) {
        return get(0, l, r, 0, size).mx;
    }

    void update(int v, int ind, int x, int tl, int tr) {
        if (tr - tl == 1) {
            t[v] = {x};
            return;
        }
        int mid = (tl + tr) / 2;
        if (ind < mid) {
            update(v * 2 + 1, ind, x, tl, mid);
        } else {
            update(v * 2 + 2, ind, x, mid, tr);
        }
        t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
    }

    void update(int ind, int x) {
        update(0, ind, x, 0, size);
    }
};

struct node {
    int x, type;
};

void dany() {
    int n,q;
    cin >> n>>q;
    vector<pair<int,int>> a(n);
    vector<node> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first>>a[i].second;
        s.push_back({a[i].first, 1});
        s.push_back({a[i].second, -1});
    }
    sort(all(s),[&](node n1, node n2) {
        return n1.x<n2.x;
    });
    int cntr=0,cnt=0,mx=0;
    vector<int> res(n+2,MAX),ans(n+1,MAX);
    for (int i=0;i<2*n;i++) {
        if (s[i].type==1) {
            cnt++;
        }
        else {
            cnt--;
            cntr++;
        }
        mx=max(mx, cnt);
        for (int i=0;i<=cnt;i++) {
            res[i]=0;
        }
        int r=min(cntr,n-cnt-cntr)*2+cnt;
        ans[r]=min(ans[r], min(cntr,n-cnt-cntr));
    }
    for (int i=n;i>=0;i--) {
        res[i]=min(res[i+1],ans[i]);
        if (i>1) {
            ans[i-2]=min(ans[i-2],ans[i]-1);
        }
    }
    for (int i=0;i<=mx;i++) {
        res[i]=0;
    }
    while (q--) {
        int x;
        cin>>x;
        cout<<res[x]<<'\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin>>t;
    while (t--) {
        dany();
    }
    return 0;
}
