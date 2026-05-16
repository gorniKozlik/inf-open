#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;
using ll = long long;
using ld = long double;

const int inf = (int)1e9 + 5;

struct SegmentTree {
	vector<int> tree;
	int size;
	void init(int n) {
		size = 1;
		while (size < n) size *= 2;
		tree.assign(2 * size - 1, inf);
	}
	void update(int lx, int rx, int l, int r, int v) {
		if (rx <= l || r <= lx) return;
		if (lx <= l && r <= rx) {
			tree[v] = std::min(tree[v], l - lx);
			return;
		}
		int m = (l + r) >> 1;
		update(lx, rx, l, m, 2 * v + 1);
		update(lx, rx, m, r, 2 * v + 2);
	}
	void update(int l, int r, int x) {
		update(l, r + 1, 0, size, 0);
	}
	int get(int x, int l, int r, int v) {
		if (l + 1 == r) {
			return tree[v];
		}
		int res = tree[v] + x - l;
		int m = (l + r) >> 1;
		if (x < m) {
			res = std::min(res, get(x, l, m, 2 * v + 1));
		} else {
			res = std::min(res, get(x, m, r, 2 * v + 2));
		}
		return res;
	}
	int get(int x) {
		return get(x, 0, size, 0);
	}
};

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n, q;
	cin >> n >> q;

	vector<int> l(n), r(n);
	for (int i = 0; i < n; ++i) {
		cin >> l[i] >> r[i];
	}

	vector<array<int, 3>> events;
	for (int i = 0; i < n; ++i) {
		events.push_back({l[i], -1, i});
		events.push_back({r[i], 1, i});
	}

	sort(events.begin(), events.end());
	
	SegmentTree st_odd, st_even;
	st_odd.init(2 * n + 5);
	st_even.init(2 * n + 5);

	vector<int> res(n + 1, inf);

	int active = 0, found = 0, handled = 0;

	for (const array<int, 3> &event : events) {
		if (event[1] == 1) {
			if (handled < n - found) {
				int take = active + 2 * std::min(handled, n - found) + 1;
				res[take] = std::min(res[take], std::min(handled, n - found) + 1);
			}
			if (active % 2 == 1) {
				st_odd.update(active / 2, active / 2 + std::min(handled, n - found), 0);
			} else {
				st_even.update(active / 2, active / 2 + std::min(handled, n - found), 0);
			}
			handled++;
		} else {
			found++;
		}
		active -= event[1];
	}

	active = found = handled = 0;

	sort(events.rbegin(), events.rend());

	for (const array<int, 3> &event : events) {
		if (event[1] == -1) {
			if (handled < n - found) {
				int take = active + 2 * std::min(handled, n - found) + 1;
				res[take] = std::min(res[take], std::min(handled, n - found) + 1);
			}
			if (active % 2 == 1) {
				st_odd.update(active / 2, active / 2 + std::min(handled, n - found), 0);
			} else {
				st_even.update(active / 2, active / 2 + std::min(handled, n - found), 0);
			}
			handled++;
		} else {
			found++;
		}
		active += event[1];
	}

	for (int i = 0; i <= n; ++i) {
		if (i % 2 == 0) {
			res[i] = std::min(res[i], st_even.get(i / 2));
		} else {
			res[i] = std::min(res[i], st_odd.get(i / 2));
		}
	}

	for (int i = n - 1; i >= 0; --i) {
		res[i] = std::min(res[i], res[i + 1]);
	}

	while (q--) {
		int k;
		cin >> k;
		cout << res[k] << ' ';
	}
}
