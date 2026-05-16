#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <deque>
#include <queue>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>
using namespace std;

#define ll long long
#define ld long double
#define all(a) (a).begin(),(a).end()
#define rall(a) (a).rbegin(),(a).rend()
mt19937 rnd(time(0));

int bin_pow(int x, int y) {
	if (y == 0) return 1;
	if (y % 2 == 0) {
		int b = bin_pow(x, y / 2);
		return b * b;
	}
	else {
		return  x * bin_pow(x, y - 1);
	}
}


struct segtree {
	int sz;
	vector<int> tree;
	vector<int> push;
	void init(int n) {
		sz = 1;
		while (sz < n) {
			sz *= 2;
		}
		tree.assign(2 * sz - 1, 0);
		push.assign(2 * sz - 1, 0);
	}
	void apply(int x, int v) {
		push[x] += v;
		tree[x] += v;
	}
	void Push(int x) {
		if (push[x] == 0) {
			return;
		}
		apply(2 * x + 1, push[x]);
		apply(2 * x + 2, push[x]);
		push[x] = 0;
	}
	void add_el(int x, int l, int r, int v, int lx, int rx) {
		if (lx >= r or rx <= l) {
			return;
		}
		if (lx >= l and rx <= r) {
			tree[x] += v;
			push[x] += v;
			return;
		}
		int m = (lx + rx) / 2;
		Push(x);
		add_el(2 * x + 1, l, r, v, lx, m);
		add_el(2 * x + 2, l, r, v, m, rx);
		tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
	}
	void add_el(int l, int r, int v) {
		add_el(0, l, r, v,0, sz);
	}
	int get_max() {
		return tree[0];
	}
};
vector<int> b;
int get_el(int v) {
	v = lower_bound(all(b), v) - b.begin();
	return v;
}

int inf = 1e9 + 100;
const int maxn = 4e5 + 100;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
		b.push_back(a[i].first);
		b.push_back(a[i].second);
	}
	sort(all(b));
	b.resize(unique(all(b)) - b.begin());
	set<pair<int, int>> st;
	//cout << '\n';
	for (int i = 0; i < n; i++) {
		a[i].first = get_el(a[i].first);
		a[i].second = get_el(a[i].second);
		st.insert({ a[i].first,a[i].second });
		//cout << a[i].first << " " << a[i].second << "\n";
	}
	//cout << '\n';
	vector<int> mn(n + 1, inf);
	segtree tree;
	tree.init(maxn);
	for (int i = 0; i < n; i++) {
		tree.add_el(a[i].first, a[i].second + 1,1);
	}
	mn[tree.get_max()] = 0;
	int k = 0;
	while (st.size() > 1) {
		pair<int, int> p1 = *st.begin();
		st.erase(p1);
		pair<int, int> p2 = *st.rbegin();
		if (p2.first <= p1.second) continue;
	//	cout << p1.first << " " << p1.second << "   " << p2.first << " " << p2.second << '\n';
		int l = p1.second;
		int r = p2.first;
		
	//	cout << l + 1 << " " << r << '\n';
		st.erase(p2);
		tree.add_el(p1.first, p1.second + 1, -1);

		tree.add_el(p2.first, p2.second + 1, -1);

		st.insert({ p1.first,p2.first });
		st.insert({ p1.second, p2.second });

		tree.add_el(p1.first, p2.first + 1, 1);

		tree.add_el(p1.second, p2.second + 1, 1);
		k++;
		if (k > n) exit(3);
		int mins = tree.get_max();
		mn[mins] = min(mn[mins], k);
	}
	for (int i = n - 1; i >= 0; i--) {
		mn[i] = min(mn[i], mn[i + 1]);
	}
	while (m--) {
		int k;
		cin >> k;
		if(mn[k] == inf) exit(3);
		cout << mn[k] << " ";
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	solve();
}