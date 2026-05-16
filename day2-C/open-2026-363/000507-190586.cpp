#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MN = -1e8, MX = 1e8;

struct point{
    int mn;
    int mx;
    int s;
    int push;
};

struct tree{
    vector<point> tr;
    int n;

    void build(vector<int> &a){
        n = a.size();
        tr.resize(4 * n);
        build0(a, 1, 0, n);
    }

    void build0(vector<int> &a, int v, int l, int r){
        if(r - l == 1){
            tr[v].mn = a[l];
            tr[v].mx = a[l];
            tr[v].s = a[l];
            return;
        }
        int mid = (r + l) / 2, u = v * 2;
        build0(a, u, l, mid);
        build0(a, u + 1, mid, r);
        tr[v].mn = min(tr[u].mn, tr[u + 1].mn);
        tr[v].mx = max(tr[u].mx, tr[u + 1].mx);
        tr[v].s = tr[u].s + tr[u + 1].s;
        tr[v].push = 0;
    }

    point get(int l1, int r1){
        return get0(1, 0, n, l1, r1);
    }

    point get0(int v, int l, int r, int l1, int r1){
        if(l >= r1 || r <= l1)
            return {MX, MN, 0, 0};
        if(l1 <= l && r <= r1){
            return tr[v];
        }
        int mid = (r + l) / 2, u = v * 2;
        point p1 = get0(u, l, mid, l1, r1);
        point p2 = get0(u + 1, mid, r, l1, r1);
        point ans;
        ans.mn = min(p1.mn, p2.mn);
        ans.mx = max(p1.mx, p2.mx);
        ans.s = p1.s + p2.s;
        return ans;
    }

    void update(int l, int r, int x){
        update0(1, 0, n, l, r, x);
    }

    void update0(int v, int l, int r, int l1, int r1, int x){
        if(l >= r1 || r <= l1)
            return;
        if(l1 <= l && r <= r1){
            tr[v].mn += x;
            tr[v].mx += x;
            tr[v].s += x * (r - l);
        }
        int mid = (r + l) / 2, u = v * 2;
        update0(u, l, mid, l1, r1, x);
        update0(u + 1, mid, r, l1, r1, x);
        tr[v].mn = min(tr[u].mn, tr[u + 1].mn);
        tr[v].mx = max(tr[u].mx, tr[u + 1].mx);
        tr[v].s = tr[u].s + tr[u + 1].s;
    }
};

signed main(){
    int n, q;
    cin >> n >> q;
    set<pair<int, int>> ev;
    for(int i = 0; i < n; ++i){
        int l, r;
        cin >> l >> r;
        ev.insert({l, 1});
        ev.insert({r, -1});
    }
    vector<int> b;
    int balance = 0;
    for(auto p: ev){
        balance += p.second;
        b.push_back(balance);
    }
    vector<int> ans(n);
    for(int i = 0; i < n; ++i){
        if(i == 0)
            ans[n - i - 1] = n - b[n - 1];
        else
            ans[n - i - 1] = min(max(ans[n - i] - 1, (int)0), min(n - i - b[n - i - 1], n - i - b[n + i - 1]));
    }
    //for(int x: b)
        //cout << x << ' ';
    //cout << '\n';
    for(int i = 0; i < q; ++i){
        int t;
        cin >> t;
        cout << (ans[t - 1] + 1) / 2 << ' ';
    }
}
