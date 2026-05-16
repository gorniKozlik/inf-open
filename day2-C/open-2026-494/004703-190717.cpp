#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <bitset>
#include <random>
#include <queue>
using namespace std;
#pragma GCC target("avx,avx2,tune=native,sse,sse2")
#define int long long

const int mod = 998244353;

inline bool vsuprun() {
	static int it = 0;
	static bool done = false;
	if (it++ == 5) {
		it = 0;
		if (1.0 * clock() / CLOCKS_PER_SEC > 0.9) {
			done = true;
		}
	}
	return done;
}

int binpow(int a, int b) {
	if (b == 0) {
		return 1;
	}
	int t = binpow(a, b / 2);
	if (b % 2 == 0) {
		return (t * t) % mod;
	}
	return (((t * t) % mod) * a) % mod;
}

struct SegmentTree {
	struct Node {
		int sum = 0;
	};

	Node combine(Node a, Node b) {
		return { a.sum + b.sum };
	}

	vector<Node> tree;
	int size = 0;

	void init(int n) {
		size = 1;
		while (size <= n) {
			size *= 2;
		}
		tree.assign(size * 2 - 1, Node());
	}

	void build(vector<int>& a) {
		int n = static_cast<int>(a.size());
		init(n);
		for (int i = 0; i < n; ++i) {
			tree[i + size - 1] = { a[i] };
		}
		for (int i = size - 2; i >= 0; --i) {
			tree[i] = combine(tree[i * 2 + 1], tree[i * 2 + 2]);
		}
	}

	void set(int i, int v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			tree[x] = { v };
			return;
		}
		int mid = (lx + rx) / 2;
		if (i < mid) {
			set(i, v, x * 2 + 1, lx, mid);
		}
		else {
			set(i, v, x * 2 + 2, mid, rx);
		}
		tree[x] = combine(tree[x * 2 + 1], tree[x * 2 + 2]);
	}

	void set(int i, int v) {
		set(i, v, 0, 0, size);
	}

	Node get(int l, int r, int x, int lx, int rx) {
		if (lx >= l && rx <= r) {
			return tree[x];
		}
		if (lx >= r || rx <= l) {
			return Node();
		}
		int mid = (lx + rx) / 2;
		return combine(get(l, r, x * 2 + 1, lx, mid), get(l, r, x * 2 + 2, mid, rx));
	}

	int get(int l, int r) {
		return get(l, r, 0, 0, size).sum;
	}
};


signed main() {
	int n, m, k, x;
	cin >> n >> m >> k >> x;
	vector<int> h(n);
	vector<int> r(n);
	for (int i = 0; i < n; ++i) {
		cin >> h[i] >> r[i];
	}
	vector<pair<int, int>> a(m);
	for (int i = 0; i < m; ++i) {
		cin >> a[i].second >> a[i].first;
	}
	if (k == 1) {
		vector<pair<int, int>> v;
		sort(a.begin(), a.end());
		reverse(a.begin(), a.end());
		int mn = 1e18;
		for (int i = 0; i < m; ++i) {
			if (a[i].first < mn) {
				v.push_back({ a[i].second, a[i].first });
				mn = a[i].first;
			}
		}
		sort(v.begin(), v.end());
		bool fl = 1;
		int money = x;
		for (int i = 0; i < n; ++i) {
			int l = -1, rr = v.size();
			while (rr - l > 1) {
				int m = (l + rr) / 2;
				if (v[m].first >= h[i]) {
					rr = m;
				}
				else {
					l = m;
				}
			}
			//cout << i << ' ' << x << ' ' << rr << ' ' << v.size() << ' ' << v[rr].second << endl;
			if (rr < v.size() && v[rr].second <= x) {
				x -= v[rr].second;
				x += r[i];
			}
			else {
				fl = 0;
				break;
			}
		}
		if (fl == 1) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}
	return 0;
}