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
		if (1.0 * clock() / CLOCKS_PER_SEC > 0.8) {
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

struct Node1 {
	int bal, l, r;
};

signed main() {
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> a(n);
	set<int> st;
	unordered_map<int, int> mp;
	for (int i = 0; i < n; ++i) {
		cin >> a[i].first >> a[i].second;
		st.insert(a[i].first);
		st.insert(a[i].second);
	}
	vector<int> k(q);
	for (int i = 0; i < q; ++i) {
		cin >> k[i];
	}
	int prev = 1;
	for (auto it : st) {
		mp[it] = prev;
		prev++;
	}
	for (int i = 0; i < n; ++i) {
		a[i].first = mp[a[i].first];
		a[i].second = mp[a[i].second];
	}
	vector<pair<int, int>> t(2 * n);
	for (int i = 0; i < n; ++i) {
		t[i * 2] = { a[i].first, 1 };
		t[i * 2 + 1] = { a[i].second, -1 };
	}
	sort(t.begin(), t.end());
	int bal = 0;
	vector<int> ans(n + 1, 1e18);
	vector<Node1> vsp(2 * n);
	vector<int> h(n + 1, 1e18);
	int mx = 0;
	ans[0] = 0;
	for (int i = 0; i < t.size(); ++i) {
		if (t[i].second == 1) {
			bal++;
			mx = max(mx, bal);
			vsp[i] = { bal, i + 1 - bal, 2 * n - i - 1 - bal };
			ans[bal] = 0;
		}
		else {
			mx = max(mx, bal);
			vsp[i] = { bal, i - bal, 2 * n - i - bal };
			ans[bal] = 0;
			bal--;
		}
	}
	for (int i = 0; i <= mx; ++i) {
		h[i] = 0;
	}
	for (int i = 0; i < 2 * n; ++i) {
		int bal = vsp[i].bal;
		int l = vsp[i].l;
		int r = vsp[i].r;
		//cout << i << ' ' << t[i].first << ' ' << bal << ' ' << l << ' ' << r << endl;
		int op = 0;
		while (l >= 1) {
			//cout << "operations " << op << ' ' << l << ' ' << r << ' ' << bal << endl;
			if (l >= 2 && r >= 2) {
				bal += 2;
				op++;
				l -= 2;
				r -= 2;
				h[bal] = min(h[bal], op);
			}
			else if (l >= 2) {
				op++;
				bal++;
				l -= 2;
				h[bal] = min(h[bal], op);
			}
			else {
				break;
			}
		}
	}
	for (int i = 0; i < q; ++i) {
		cout << h[k[i]] << ' ';
	}
	cout << endl;
	return 0;
}