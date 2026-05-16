#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <random>
#include <cmath>

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#pragma GCC target("popcnt")

#define int long long
#define all(a) a.begin(),a.end()
#define endl '\n'
#define pii pair<int, int>
#define pb emplace_back
typedef long double ld;

int const N = 4e5 + 5, M = 1e2 + 5, lg = 23, INF = 2e9;
int mod = 998244353, mod2 = 1e9 + 9;
int P = 1e9 + 7;


int tree[4 * N];
int wantpush[4 * N];
int s = 1;

void push(int l, int r, int ind) {
	tree[ind] += wantpush[ind];
	if (r - l > 1) {
		wantpush[ind * 2] += wantpush[ind];
		wantpush[ind * 2 + 1] += wantpush[ind];
	}
	wantpush[ind] = 0;
}

int getmax(int lq, int rq, int l = 0, int r = s, int ind = 1) {
	push(l, r, ind);
	if (r <= lq || rq <= l) {
		return 0;
	}
	if (lq <= l && r <= rq) {
		return tree[ind];
	}
	int mid = (r + l) / 2;
	return max(getmax(lq, rq, l, mid, ind * 2), getmax(lq, rq, mid, r, ind * 2 + 1));
}

void upd(int x, int lq, int rq, int l = 0, int r = s, int ind = 1) {
	push(l, r, ind);
	if (r <= lq || rq <= l) {
		return;
	}
	if (lq <= l && r <= rq) {
		wantpush[ind] += x;
		push(l, r, ind);
		return;
	}
	int mid = (r + l) / 2;
	upd(x, lq, rq, l, mid, ind * 2);
	upd(x, lq, rq, mid, r, ind * 2 + 1);
	tree[ind] = max(tree[ind * 2], tree[ind * 2 + 1]);
}

struct event {
	int x, ind, newval;
};

void compress(vector<event>& p) {
	sort(all(p), [](event a, event b) {
		return a.x < b.x;
		});
	int cnt = 0;
	for (event& e : p) {
		e.newval = cnt++;
	}
}

void propush(int l = 0, int r = s, int ind = 1) {
	push(l, r, ind);
	int mid = (r + l) / 2;
	if (r - l == 1) return;
	propush(l, mid, ind * 2);
	propush(mid, r, ind * 2 + 1);
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q; cin >> n >> q;

	multiset<pii> l, r;

	vector<int> k(q);

	while (s < 2 * n) s <<= 1;

	vector<event> e;

	for (int i = 0; i < n; ++i) {
		int a, b; cin >> a >> b;
		e.push_back({ a, i, 0 });
		e.push_back({ b, i, 0 });
	}
	for (int& i : k) cin >> i;

	compress(e);

	sort(all(e), [](event a, event b) {
		return a.ind < b.ind || (a.ind == b.ind && a.x < b.x);
		});
	
	for (int i = 0; i < e.size(); i += 2) {
		upd(1, e[i].newval, e[i + 1].newval + 1);
		l.insert({ e[i + 1].newval, e[i].newval });
		r.insert({ e[i].newval, e[i + 1].newval });
	}
	
	int ops = 0;

	vector<int> ans(n + 4, -1);

	ans[getmax(0, 2 * n + 1)] = 0;

	for (int i = 0; i < n; ++i) {
		pii a = *l.begin();
		pii b = *r.rbegin();
		if (a == b) continue;
		if (a.first < b.first) {
			propush();
			//for (int i = s; i < s + 2 * n; ++i) {
			//	cout << tree[i] << ' ';
			//}
			//cout << endl;
			ops++;
			upd(1, a.first, b.first + 1);
			upd(1, a.first + 1, b.first);
			ans[getmax(0, 2 * n + 1)] = ops;
		}
		l.erase(l.begin());
		r.erase(--r.end());
	}

	for (int i = n + 2; i >= 1; --i) {
		if (ans[i] == -1) ans[i] = ans[i + 1];
	}

	for (int i : k) {
		cout << ans[i] << ' ';
	}

	return 0;
}