// #pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
using ld = long double;

#define all(x) (x).begin(), (x).end()
#define len(x) (int)((x).size())
#define endl '\n'

template<typename T, typename U> bool remin(T& a, const U& b) { return (T)(b) < (a) ? a = (T)(b), 1 : 0; }
template<typename T, typename U> bool remax(T& a, const U& b) { return (a) < (T)(b) ? a = (T)(b), 1 : 0; }
template<typename T> istream& operator>>(istream& in, vector<T>& a) { for (T& x : a) { in >> x; } return in; }
template<typename T> ostream& operator<<(ostream& out, vector<T>& a) { for (T& x : a) { out << x << ' ';  } return out; }

struct Node {
	int val;
	int add;
	Node(int val = 0, int add = 0) : val(val), add(add) { }
};

struct SegmentTree {
	int n;
	vector<Node> tree;

	void unite(int x) {
		tree[x].val = max(tree[x << 1].val, tree[x << 1 | 1].val);
	}

	SegmentTree(int n_) {
		n = 1 << (__lg(n_ - 1) + 1);
		tree.resize(n << 1);
	}

	void apply(int x, int lx, int rx, int val) {
		tree[x].val += val;
		tree[x].add += val;
	}

	void push(int x, int lx, int rx) {
		if (lx + 1 == rx || tree[x].add == 0) return;
		int mx = (lx + rx) >> 1;
		apply(x << 1, lx, mx, tree[x].add);
		apply(x << 1 | 1, mx, rx, tree[x].add);
		tree[x].add = 0;
	}

	void update(int x, int lx, int rx, int lq, int rq, int val) {
		if (rq <= lx || rx <= lq) return;
		push(x, lx, rx);
		if (lq <= lx && rx <= rq) {
			apply(x, lx, rx, val);
			return;
		}
		int mx = (lx + rx) >> 1;
		update(x << 1, lx, mx, lq, rq, val);
		update(x << 1 | 1, mx, rx, lq, rq, val);
		unite(x);
	}

	int get() {
		push(1, 0, n);
		return tree[1].val;
	}
};

void solve() {
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> a(n);
	int minl = INT_MAX, maxr = INT_MIN;
	for (auto& [x, y] : a) {
		cin >> x >> y;
		if (remin(minl, x)) {
			maxr = y;
		} else if (minl == x) {
			remax(maxr, y);
		}
	}
	vector<pair<int, int>> A = a;
	vector<pair<int, int>> k(q);
	for (int i = 0; i < q; ++i) {
		cin >> k[i].first;
		k[i].second = i;
	}
	sort(all(k));
	vector<int> ans(q, INT_MAX);
	vector<int> comp;
	for (auto& [x, y] : a) {
		comp.push_back(x);
		comp.push_back(y);
	}
	sort(all(comp));
	comp.resize(unique(all(comp)) - comp.begin());
	auto get = [&](int x) -> int {
		return lower_bound(all(comp), x) - comp.begin();
	};
	set<int> l, r;
	set<pair<int, int>> seg;
	set<pair<int, int>> rseg;
	for (auto& [x, y] : a) {
		x = get(x);
		y = get(y);
		l.insert(x);
		r.insert(y);
		seg.emplace(x, y);
		rseg.emplace(y, x);
	}
	SegmentTree st(len(comp) + 10);
	for (auto& [x, y] : seg) {
		st.update(1, 0, st.n, x, y + 1, 1);
	}
	int op = 0;
	vector<pair<int, int>> val;
	while (len(seg)) {
		int mx = st.get();
		val.emplace_back(mx, op);
		if (seg.find({*l.begin(), *r.rbegin()}) != seg.end()) {
			seg.erase({*l.begin(), *r.rbegin()});
			rseg.erase({*r.rbegin(), *l.begin()});
			l.erase(l.begin());
			r.erase((--r.end()));
		}
		if (len(seg) < 2) break;
		auto it = seg.lower_bound({*l.begin(), -1});
		auto itt = rseg.lower_bound({*r.rbegin(), -1});
		st.update(1, 0, st.n, it->first, it->second + 1, -1);
		st.update(1, 0, st.n, itt->second ,itt->first + 1, -1);
		st.update(1, 0, st.n, it->first, itt->first + 1, 1);
		st.update(1, 0, st.n, min(it->second, itt->second), max(it->second, itt->second) + 1, 1);
		// for (int i = it->first; i <= it->second; ++i) {
		// 	c[i]--;
		// }
		// for (int i = itt->second; i <= itt->first; ++i) {
		// 	c[i]--;
		// }
		// for (int i = it->first; i <= itt->first; ++i) {
		// 	c[i]++;
		// }
		// for (int i = min(it->second, itt->second); i <= max(it->second, itt->second); ++i) {
		// 	c[i]++;
		// }
		auto del1 = *it, del2 = *itt;
		l.erase(it->first);
		l.erase(itt->second);
		r.erase(itt->first);
		r.erase(it->second);
		seg.erase({itt->second, itt->first});
		rseg.erase({it->second, it->first});
		seg.erase(del1);
		rseg.erase(del2);
		++op;
	}
	int mx = st.get();
	val.emplace_back(mx, op);
	int iter = 0;
	int j = 0;
	while (iter < len(val)) {
		while (j < q && k[j].first <= val[iter].first) {
			ans[k[j].second] = val[iter].second;
			++j;
		}
		++iter;
	}
	// for (int i = 0; i < q; ++i) {
	// 	cout << ans[i] << ' ';
	// }
	a = A;
	set<array<int, 3>> S;
	for (auto& [x, y] : a) {
		S.insert({y - x + 1, x, y});
	}
	SegmentTree st1(len(comp) + 10);
	for (auto& [ln, x, y] : S) {
		st1.update(1, 0, st1.n, x, y + 1, 1);
	}
	op = 0;
	val.clear();
	while (len(S) > 1) {
		int mx = st1.get();
		val.emplace_back(mx, op);
		array<int, 3> a1 = *S.begin();
		array<int, 3> a2 = *(next(S.begin()));
		st1.update(1, 0, st1.n, a1[1], a1[2] + 1, -1);
		st1.update(1, 0, st1.n, a2[1], a2[2] + 1, -1);
		st1.update(1, 0, st1.n, min(a1[1], a2[1]), max(a1[2], a2[2]), 1);
		int an1 = a1[1] + a2[1] - min(a1[1], a2[1]);
		int an2 = a1[2] + a2[2] - max(a1[2], a2[2]);
		st1.update(1, 0, st1.n, min(an1, an2), max(an1, an2) + 1, 1);
		S.erase(S.begin());
		S.erase(S.begin());
		++op;
	}
	mx = st.get();
	val.emplace_back(mx, op);
	iter = 0;
	j = 0;
	while (iter < len(val)) {
		while (j < q && k[j].first <= val[iter].first) {
			remin(ans[k[j].second], val[iter].second);
			++j;
		}
		++iter;
	}
	for (int i = 0; i < q; ++i) {
		cout << ans[i] << ' ';
	}
}

int32_t main() {
#ifdef LOCAL
	freopen("C://work//open1//in.txt", "r", stdin);
	freopen("C://work//open1//out.txt", "w", stdout);
#endif
int test = 1;
// cin >> test;
while (test--) {
	solve();
}
return 0;
}