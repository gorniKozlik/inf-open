#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18, MOD = 1e9 + 7;
mt19937 rnd(time(0));

void solve();

vector<int> t;
vector<int> c;
void push(int v, int l, int r){
    if (l + 1 == r || c[v] == 0){return;}
    t[2 * v + 1] += c[v];
    t[2 * v + 2] += c[v];
    c[2 * v + 1] += c[v];
    c[2 * v + 2] += c[v];
    c[v] = 0;
}
void update(int v, int l, int r, int tl, int tr, int x){
    if (l >= tr || r <= tl){return;}
    if (l >= tl && r <= tr){
        t[v] += x;
        c[v] += x;
        return;
    }
    push(v, l, r);
    int m = (l + r) / 2;
    update(2 * v + 1, l, m, tl, tr, x);
    update(2 * v + 2, m, r, tl, tr, x);
    t[v] = max(t[2 * v + 1], t[2 * v + 2]);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> x;
    set <pair<int, int>> p1;
    set <pair<int, int>> p2;
    vector<pair<int, int>> rb(n);
    for (int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        rb[i] = {l, r};
        x.push_back(l);
        x.push_back(l + 1);
        x.push_back(r + 1);
        x.push_back(r);
        p1.insert({l, i});
        p2.insert({r, i});
    }
    sort(x.begin(), x.end());
    t.resize(16 * n);
    c.resize(16 * n);
    for (int i = 0; i < n; i++){
        int pos1 = lower_bound(x.begin(), x.end(), rb[i].first) - x.begin();
        int pos2 = upper_bound(x.begin(), x.end(), rb[i].second) - x.begin();
        update(0, 0, 2 * n, pos1, pos2, 1);
    }
    vector<int> ans(n + 1);
    int c = 0;
    for (int i = 1; i < n + 1; i++){
        while (t[0] < i && (int)p1.size() > 0 && (int)p2.size() > 0){
            auto x1 = *p1.begin(), x2 = *p2.rbegin();
            p1.erase(p1.begin());
            p2.erase(--p2.end());
            p2.erase({rb[x1.second].second, x1.second});
            p1.erase({rb[x2.second].first, x2.second});
            if (x1.second == x2.second){
                continue;
            }
            c++;
            int p11 = lower_bound(x.begin(), x.end(), rb[x1.second].first) - x.begin();
            int p12 = upper_bound(x.begin(), x.end(), rb[x1.second].second) - x.begin();
            int p21 = lower_bound(x.begin(), x.end(), rb[x2.second].first) - x.begin();
            int p22 = upper_bound(x.begin(), x.end(), rb[x2.second].second) - x.begin();
            update(0, 0, 4 * n, p11, p12, -1);
            update(0, 0, 4 * n, p21, p22, -1);
            swap(rb[x1.second].second, rb[x2.second].second);
            if (rb[x2.second].first > rb[x2.second].second){
                swap(rb[x2.second].first, rb[x2.second].second);
            }
            p1.insert({rb[x2.second].first, x2.second});
            p2.insert({rb[x2.second].second, x2.second});
            p11 = lower_bound(x.begin(), x.end(), rb[x1.second].first) - x.begin();
            p12 = upper_bound(x.begin(), x.end(), rb[x1.second].second) - x.begin();
            p21 = lower_bound(x.begin(), x.end(), rb[x2.second].first) - x.begin();
            p22 = upper_bound(x.begin(), x.end(), rb[x2.second].second) - x.begin();
            update(0, 0, 2 * n, p11, p12, 1);
            update(0, 0, 2 * n, p21, p22, 1);
        }
        ans[i] = c;
    }
    while (q--){
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }
}
