#include <bits/stdc++.h>
using namespace std;

int lb(vector<int> &v, int x){
    return lower_bound(v.begin(), v.end(), x) - v.begin();
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, qq;
    cin >> n >> qq;
    vector<int> c, l(n), r(n);
    for(int i = 0; i < n; ++i){
        cin >> l[i] >> r[i];
        c.push_back(l[i]);
        c.push_back(r[i]);
    }
    sort(c.begin(), c.end());
    vector<int> b(2*n, 1);
    for(int x : r){
        b[lb(c, x)] = -1;
    }
    vector<int> a(2*n + 1);
    for(int i = 0; i < 2*n; ++i){
        a[i + 1] = a[i] + b[i];
    }
    vector<int> m(2*n + 1);
    m[n] = a[n];
    for(int i = n - 1; i >= 0; --i){
        m[i] = max(m[i + 1], a[i]);
    }
    for(int i = n + 1; i <= 2*n; ++i){
        m[i] = max(m[i - 1], a[i]);
    }
    vector<int> x = {max(m[0], m[2*n])};
    int p = 0, q = 2*n - 1, d = 0;
    while(x.back() < n){
        while(b[p] == 1) ++p;
        while(b[q] == -1) --q;
        b[p] = 1;
        b[q] = -1;
        d += 2;
        x.push_back(max(m[p + 1], m[q]) + d);
    }
    for(int it = 0; it < qq; ++it){
        int k;
        cin >> k;
        cout << lb(x, k) << endl;
    }
}