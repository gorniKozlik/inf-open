#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <numeric>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <queue>

#define all(a) a.begin(), a.end()

const int INF = 1e9;

using namespace std;

struct seg {
	int l, r, ind;
};


void compress(vector<seg>& a) {
	int n = a.size();
	set<int> s;
	for (int i = 0; i < n; ++i) {
		s.insert(a[i].l);
		s.insert(a[i].r);
	}
	map<int, int> mp;
	int t = 0;
	for (int i : s) {
		mp[i] = t++;
	}
	for (int i = 0; i < n; ++i) {
		a[i].l = mp[a[i].l];
		a[i].r = mp[a[i].r];
	}
}

vector<int> tree, lazy;

void push(int v) {
	tree[v] += lazy[v];
	lazy[v * 2 + 1] += lazy[v];
	lazy[v * 2 + 2] += lazy[v];
	lazy[v] = 0;
}

void recalc(int v) {
	tree[v] = max(tree[v * 2 + 1] + lazy[v * 2 + 1], tree[v * 2 + 2] + lazy[v * 2 + 2]) + lazy[v];
}

void upd(int v, int l, int r, int L, int R) {
	push(v);
	if (r < L || R < l) return;
	if (L <= l && r <= R) {
		lazy[v] += 1;
		push(v);
		return;
	}
	int mid = (l + r) / 2;
	upd(v * 2 + 1, l, mid, L, R);
	upd(v * 2 + 2, mid + 1, r, L, R);
	recalc(v);
}

int get_t(int v, int l, int r, int L, int R) {
	push(v);
	if (r < L || R < l) return 0;
	if (L <= l && r <= R) return tree[v];
	int mid = (l + r) / 2;
	int res1 = get_t(v * 2 + 1, l, mid, L, R);
	int res2 = get_t(v * 2 + 2, mid + 1, r, L, R);
	return max(res1, res2);
}

bool cmpa(seg a, seg b) {
	return a.r < b.r;
}

bool cmpb(seg a, seg b) {
	return a.l > b.l;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<seg> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i].l >> a[i].r;
		a[i].ind = i;
	}
	compress(a);
	tree.resize(16 * n + 1);
	lazy.resize(16 * n + 1);
	int SZ = 2 * n;
	for (int i = 0; i < n; ++i) {
		upd(0, 0, SZ - 1, a[i].l + 1, a[i].r);
	}
	vector<seg> b = a;
	sort(all(a), cmpa);
	sort(all(b), cmpb);
	vector<bool> used(n, false);
	int x = 0, y = 0;
	vector<int> mx;
	mx.push_back(get_t(0, 0, SZ - 1, 0, SZ - 1));
	while (true) {
		if (x == n || y == n) break;
		if (used[a[x].ind]) {
			++x;
			continue;
		}
		if (used[b[y].ind]) {
			++y;
			continue;
		}
		if (a[x].r + 1 > b[y].l) break;
		used[a[x].ind] = true;
		used[b[y].ind] = true;
		upd(0, 0, SZ - 1, a[x].r + 1, b[y].l);
		upd(0, 0, SZ - 1, a[x].r + 1, b[y].l);
		++x;
		++y;
		mx.push_back(get_t(0, 0, SZ - 1, 0, SZ - 1));
	}
	vector<int> ans(2 * n + 1, INF);
	for (int i = mx.size() - 1; i >= 0; --i) {
		ans[mx[i]] = i;
	}
	for (int i = ans.size() - 2; i >= 1; --i) {
		ans[i] = min(ans[i], ans[i + 1]);
	}
	vector<int> k(q);
	for (int i = 0; i < q; ++i) {
		cin >> k[i];
	}
	for (int i = 0; i < q; ++i) {
		cout << ans[k[i]] << " ";
	}
}