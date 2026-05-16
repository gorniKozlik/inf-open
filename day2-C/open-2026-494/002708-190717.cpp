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

struct Node1 {
	int bal, l, r;
};

struct Node2 {
	int ind, mx_bal, op1, op2, bal;
};

bool compare(Node2 a, Node2 b) {
	if (a.mx_bal < b.mx_bal) {
		return true;
	}
	if (a.mx_bal > b.mx_bal) {
		return false;
	}
	return a.ind < b.ind;
}

bool compare1(Node2 a, Node2 b) {
	int sum_a = a.bal + a.op1;
	int sum_b = b.bal + b.op1;
	if (sum_a < sum_b || sum_a == sum_b && a.ind < b.ind) {
		return true;
	}
	return false;
}

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
	vector<Node2> help(2 * n);
	for (int i = 2 * n - 1; i >= 0; --i) {
		if (vsuprun()) {
			break;
		}
		int bal = vsp[i].bal;
		int l = vsp[i].l;
		int r = vsp[i].r;
		//help[i] = { i, bal + l / 2, min(l / 2, r / 2), l / 2 - min(l / 2, r / 2), bal };
		//cout << i << ' ' << t[i].first << ' ' << bal << ' ' << l << ' ' << r << endl;
		int op = 0;
		while (l >= 2) {
			//cout << "operations " << op << ' ' << l << ' ' << r << ' ' << bal << endl;
			if (l >= 2 && r >= 2) {
				bal += 2;
				op++;
				l -= 2;
				r -= 2;
				h[bal] = min(h[bal], op);
			}
			else {
				op++;
				bal++;
				l -= 2;
				h[bal] = min(h[bal], op);
			}
		}
	}
	/*vector<Node2> p = help;
	sort(p.begin(), p.end(), compare1);
	sort(help.begin(), help.end(), compare);
	int j1 = help.size() - 1;
	int u1 = 0;
	int j2 = p.size() - 1;
	int u2 = 0;
	set<pair<int, int>> st1;
	set<pair<int, int>> st2;
	for (int i = 0; i <= n; ++i) {
		while (j1 >= 0 && p[j1].bal + p[j1].op1 >= i) {
			st1.insert({ -p[j1].bal, p[j1].op1 });
			j1--;
		}
		while (u1 < p.size() && p[u1].bal + p[u1].op1 < i) {
			st1.erase(st1.find({ -p[u1].bal, p[u1].op1 }));
			u1++;
		}
		while (j >= 0 && help[j].mx_bal >= i) {
			st1.insert({ -help[j].op1 - help[j].bal, help[j].bal });
			j--;
		}
		while (u < help.size() && help[u].mx_bal < i) {
			st1.erase({ -help[u].op1 - help[u].bal, help[u].bal });
			u++;
		}
		int it = st1.begin()->first;
		int sec = st1.begin()->second;
		it *= -1;
		if (i <= mx) {
			continue;
		}
		else {
			int op = 0;

		}
	}*/
	for (int i = 0; i < q; ++i) {
		cout << h[k[i]] << ' ';
	}
	cout << endl;
	return 0;
}