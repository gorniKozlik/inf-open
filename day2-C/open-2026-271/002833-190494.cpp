#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdio>
#include <cstdint>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <random>
#include <cstring>
#include <string>
using namespace std;
#define int long long
#define all(x) (x).begin(), (x).end()
#define rep(n) for (int rep_i = 0; rep_i < n; rep_i++)
#define cin(v) for (auto& e : v) cin >> e;
#define cout(v) for (auto e : v) cout << e << " "; cout << endl;
using ll = long long;
using ull = unsigned long long;
using db = double;
using i32 = int32_t;
using vi = vector <int>;
using vll = vector <ll>;
using pii = pair <int, int>;
using pll = pair <ll, ll>;
#define sq(x) ((x) * (x))
mt19937 rng(time(0));
int rand(int l, int r) {
	return (rng() % (r - l + 1)) + l;
}
int gcd(int x, int y) {
	if (!y)
		return x;
	return gcd(y, x % y);
}
void fastw() {
	ios_base::sync_with_stdio(0); cin.tie(0);
}

void solve();

signed main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
#endif
	fastw();
	solve();
}

const int md = 998244353;

int binpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = (res * a) % md;
		}
		a = (a * a) % md;
		b >>= 1;
	}

	return res;
}

struct new_seg {
	int l, r;
	int l2, r2;

	new_seg() {}
	new_seg(int _l, int _r, int _l2, int _r2) {
		l = _l;
		r = _r;
		l2 = _l2;
		r2 = _r2;
	}
};

struct ev {
	int x, t;
	ev(int _x, int _t) {
		x = _x;
		t = _t;
	}

	bool operator<(const ev& a) const {
		return make_pair(x, t) < make_pair(a.x, a.t);
	}
};

void solve() {
	int n, q;
	cin >> n >> q;
	vector <pii> a, b;
	map <int, vector <int>> mp;
	rep(n) {
		int l, r;
		cin >> l >> r;
		mp[l].push_back(r);
		a.push_back({ l, r });
	}
	vector <int> qrs(q);
	cin(qrs);

	auto get = [&](const vector<pii>& p) {
		int r = 0;
		vector <ev> events;

		for (int i = 0; i < p.size(); i++) {
			events.push_back({ p[i].first, -1 });
			events.push_back({ p[i].second, 1 });
		}

		sort(all(events));
		int mx = 0;
		for (auto [x, t] : events) {
			int pl = -t;
			r += pl;
			mx = max(mx, r);
		}
		return mx;
	};

	int done = 0;
	vector <pii> v;
	sort(all(a));
	map <pii, int> used;
	
	vector <new_seg> order;

	for (int i = 0; i < n; i++) {
		if (used[{a[i].first, a[i].second}] == 1) continue;
		int r = a[i].second;
		int l = a[i].first;
		int left = mp.rbegin()->first;
		int right = mp[left].back();
		mp[left].pop_back();
		if (mp[left].size() == 0)
			mp.erase(left);
		used[{a[i].first, r}] = 1;
	    used[{left, right}] = 1;

		order.push_back({ l, r, left, right });
	}
	vector <pii> tmp = a;
	vector <int> rs(order.size() + 1);
	rs[0] = get(tmp);
	for (int i = 0; i < order.size(); i++) {
		int l = order[i].l;
		int r = order[i].r;
		int l2 = order[i].l2;
		int r2 = order[i].r2;
		tmp.erase(find(all(tmp), make_pair(l, r)));
		tmp.erase(find(all(tmp), make_pair(l2, r2)));
		
		vector <int> nd = { l, r, l2, r2 };
		sort(all(nd));


		tmp.push_back({ nd[0], nd[3]});
		tmp.push_back({ nd[1], nd[2]});

		rs[i + 1] = get(tmp);
	}

	for (int i = 0; i < q; i++) {
		int qr = qrs[i];
		cout << lower_bound(all(rs), qr) - rs.begin() << " ";
	}
	cout << endl;
}