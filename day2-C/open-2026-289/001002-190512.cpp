#include <bits/stdc++.h>

using namespace std;

int inf = 1e7;
vector<int> t, d, t1, d1;

void push(int v) {
    if (d[v] == -inf) return;
    t[v * 2 + 1] = d[v];
    t[v * 2 + 2] = d[v];
    d[v * 2 + 1] = d[v];
    d[v * 2 + 2] = d[v];
    d[v] = -inf;
}

void push1(int v) {
    if (d1[v] == -inf) return;
    t1[v * 2 + 1] = d1[v];
    t1[v * 2 + 2] = d1[v];
    d1[v * 2 + 1] = d1[v];
    d1[v * 2 + 2] = d1[v];
    d1[v] = -inf;
}

void update(int v, int l, int r, int ql, int qr, int delta) {
    if (l >= qr || r <= ql) return;
    if (ql <= l && r <= qr) {
        t[v] = delta;
        d[v] = delta;
        return;
    }
    int m = (l + r) / 2;
    push(v);
    update(v * 2 + 1, l, m, ql, qr, delta);
    update(v * 2 + 2, m, r, ql, qr, delta);
    t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
}

void update1(int v, int l, int r, int ql, int qr, int delta) {
    if (l >= qr || r <= ql) return;
    if (ql <= l && r <= qr) {
        t1[v] = delta;
        d1[v] = delta;
        return;
    }
    int m = (l + r) / 2;
    push1(v);
    update1(v * 2 + 1, l, m, ql, qr, delta);
    update1(v * 2 + 2, m, r, ql, qr, delta);
    t1[v] = max(t1[v * 2 + 1], t1[v * 2 + 2]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) return -inf;
    if (ql <= l && r <= qr) return t[v];
    int m = (l + r) / 2;
    push(v);
    return max(get(v * 2 + 1, l, m, ql, qr), get(v * 2 + 2, m, r, ql, qr));
}

int get1(int v, int l, int r, int ql, int qr) {
    if (l >= qr || r <= ql) return -inf;
    if (ql <= l && r <= qr) return t1[v];
    int m = (l + r) / 2;
    push1(v);
    return max(get1(v * 2 + 1, l, m, ql, qr), get1(v * 2 + 2, m, r, ql, qr));
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> a(n);
	map<int, pair<int, int>> mp;
	for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        mp[a[i].first] = {i, 1};
        mp[a[i].second] = {i, -1};
	}
	vector<pair<int, pair<int, int>>> zap, zap1;
	int cnt1 = 0, cnt2 = 0, cnt3 = n;
	for (auto [x, y] : mp) {
        if (y.second == 1) {
            cnt2++;
            cnt3--;
            int num1 = min(cnt1, cnt3);
            int num2 = max(cnt1, cnt3);
            zap.push_back({cnt2, {0, cnt2 + 2 * num1}});
            zap1.push_back({cnt2 + num1, {cnt2 + 2 * num1, cnt2 + num1 + num2}});
        } else {
            int num1 = min(cnt1, cnt3);
            int num2 = max(cnt1, cnt3);
            zap.push_back({cnt2, {0, cnt2 + 2 * num1}});
            zap1.push_back({cnt2 + num1, {cnt2 + 2 * num1, cnt2 + num1 + num2}});
            cnt1++;
            cnt2--;
        }
	}
	sort(zap.begin(), zap.end());
	sort(zap1.begin(), zap1.end());
	t.assign(n * 4 + 4, -inf);
	t1.assign(n * 4 + 4, -inf);
	d.assign(n * 4 + 4, -inf);
	d1.assign(n * 4 + 4, -inf);
	for (auto [x, y] : zap) {
        update(0, 0, n + 1, y.first, y.second + 1, x);
	}
	for (auto [x, y] : zap1) {
        update1(0, 0, n + 1, y.first, y.second + 1, x);
	}
	vector<int> ans(n + 1, -1), ans1(n + 1, -1), ans2(n + 1, -1);
	for (int i = 0; i <= n; ++i) {
        ans[i] = get(0, 0, n + 1, i, i + 1);
        ans1[i] = get1(0, 0, n + 1, i, i + 1);
        ans2[i] = min((i - ans[i] + 1) / 2, (i - ans1[i]));
	}
	while (q--) {
        int x; cin >> x;
        if (ans2[x] > n) exit(-1);
        cout << max(0, ans2[x]) << '\n';
	}
}
