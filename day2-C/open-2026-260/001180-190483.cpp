#include <bits/stdc++.h>
using namespace std;

#define int long long
using ld = long double;

#define all(x) (x).begin(), (x).end()
#define len(x) (int)((x).size())
#define endl '\n'

template<typename T, typename U> bool remin(T& a, const U& b) { return (T)(b) < (a) ? a = (T)(b), 1 : 0; }
template<typename T, typename U> bool remax(T& a, const U& b) { return (a) < (T)(b) ? a = (T)(b), 1 : 0; }
template<typename T> istream& operator>>(istream& in, vector<T>& a) { for (T& x : a) { in >> x; } return in; }
template<typename T> ostream& operator<<(ostream& out, vector<T>& a) { for (T& x : a) { out << x << ' ';  } return out; }

void solve() {
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> a(n);
	int minl = INT_MAX, maxr = INT_MIN;
	for (auto& [x, y] : a) {
		cin >> x >> y;
		remin(minl, x);
		remax(maxr, y);
	}
	vector<pair<int, int>> na;
	int cnt = 0;
	for (auto& [x, y] : a) {
		if (x == minl && y == maxr) {
			++cnt;
			continue;
		}
		na.emplace_back(x, y);
	}
	a = move(na);
	n = len(a);
	vector<int> k(q, INT_MAX);
	for (int& x : k) cin >> x;
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
	vector<int> c(len(comp) + 1, cnt);
	for (auto& [x, y] : seg) {
		for (int i = x; i <= y; ++i) {
			c[i]++;
		}
	}
	cnt = 0;
	while (len(seg)) {
		int mx = 0;
		for (int i = 0; i <= len(comp); ++i) {
			remax(mx, c[i]);
		}
		for (int i = 0; i < q; ++i) {
			if (ans[i] == INT_MAX && k[i] <= mx) {
				ans[i] = cnt;
			}
		}
		if (seg.find({*l.begin(), *r.rbegin()}) != seg.end()) {
			seg.erase({*l.begin(), *r.rbegin()});
			rseg.erase({*r.rbegin(), *l.begin()});
			l.erase(l.begin());
			r.erase(r.begin());
		}
		if (len(seg) < 2) break;
		auto it = seg.lower_bound({*l.begin(), -1});
		auto itt = rseg.lower_bound({*r.rbegin(), -1});
		for (int i = it->first; i <= it->second; ++i) {
			c[i]--;
		}
		for (int i = itt->second; i <= itt->first; ++i) {
			c[i]--;
		}
		for (int i = it->first; i <= itt->first; ++i) {
			c[i]++;
		}
		for (int i = min(it->second, itt->second); i <= max(it->second, itt->second); ++i) {
			c[i]++;
		}
		l.erase(it->first);
		l.erase(itt->second);
		r.erase(itt->first);
		r.erase(it->second);
		seg.erase({itt->second, itt->first});
		rseg.erase({it->second, it->first});
		seg.erase(it);
		rseg.erase(itt);
		++cnt;
	}
	int mx = 0;
	for (int i = 0; i <= len(comp); ++i) {
		remax(mx, c[i]);
	}
	for (int i = 0; i < q; ++i) {
		if (ans[i] == INT_MAX && k[i] <= mx) {
			ans[i] = cnt;
		}
	}
	for (int i = 0; i < q; ++i) {
		cout << ans[i] << ' ';
	}
	cout << endl;
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