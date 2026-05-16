#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

bool cmp(pll a, pll b) {
    if (a.second != b.second) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

int get_cnt(vector<ll> ls, vector<ll> rs) {
    int n = (int) ls.size();
    sort(ls.begin(), ls.end());
    sort(rs.begin(), rs.end());
    vector<int> allps;
    int l = 0, r = 0;
    while (l < n && r < n) {
        if (ls[l] < rs[r]) {
            allps.push_back(1);
            ++l;
        } else {
            allps.push_back(-1);
            ++r;
        }
    }
    while (l < n) {
        allps.push_back(1);
        ++l;
    }
    while (r < n) {
        allps.push_back(-1);
        ++r;
    }
    int cnt = 0, mx = 0;
    for (int i = 0; i < (int) allps.size(); ++i) {
        cnt += allps[i];
        mx = max(mx, cnt);
    }
    return mx;
}

vector<int> intime;

void solve(vector<ll> &ls, vector<ll> &rs) {
    int n = (int) ls.size();
    int mx = get_cnt(ls, rs), cur = 0;
    int timer = 0;
    while (mx < n && cur < n - cur - 1) {
        ++timer;
        if (rs[cur] < ls[n - cur - 1]) {
            swap(rs[cur], ls[n - cur - 1]);
            int cnt = get_cnt(ls, rs);
            if (mx < cnt) {
                mx = cnt;
            }
        }
        intime[timer] = mx;
        ++cur;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<ll> ls(n), rs(n);
    for (int i = 0; i < n; ++i) {
        cin >> ls[i] >> rs[i];
    }
    intime.assign(n, -1);
    solve(ls,rs);
    map<int, int> mp;
    for (int i = 0; i < (int) intime.size(); ++i) {
        mp[intime[i]] = i;
    }
    while (q--) {
        int k;
        cin >> k;
        cout << mp[k] << " ";
    }
    return 0;
}
