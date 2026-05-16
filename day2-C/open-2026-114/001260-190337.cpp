// TaskC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <map>

using namespace std;

using ll = long long;
using ld = long double;

const int inf = 1e9 + 7;
const int mod = 1e9 + 7;

struct Node {
	int mx = 0, s = 0, pr = 0, sf = 0;
	Node() {}
	Node(int val) : mx(max(0, val)), s(val), pr(max(0, val)), sf(max(0, val)) {}
};

vector<Node> t;

Node merge(Node l, Node r) {
	Node ans;
	ans.s = l.s + r.s;
	ans.pr = max(l.pr, l.s + r.pr);
	ans.sf = max(r.sf, r.s + l.sf);
	ans.mx = max({ l.mx, r.mx, l.sf + r.pr });
	return ans;
}

void upd(int v, int l, int r, int pos, int val) {
	if (l == r - 1) {
		t[v] = Node(val);
		return;
	}
	int m = (l + r) / 2;
	if (pos < m) {
		upd(v * 2 + 1, l, m, pos, val);
	}
	else {
		upd(v * 2 + 2, m, r, pos, val);
	}
	t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
}

Node ask(int v, int l, int r, int askl, int askr) {
	if (l >= askr || r <= askl) {
		return Node();
	}
	if (askl <= l && r <= askr) {
		return t[v];
	}
	int m = (l + r) / 2;
	return merge(ask(v * 2 + 1, l, m, askl, askr), ask(v * 2 + 2, m, r, askl, askr));
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> l(n), r(n);
	vector<pair<int, int>> ar;
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
		ar.emplace_back(l[i], 1);
		ar.emplace_back(r[i], -1);
	}
	sort(ar.begin(), ar.end());
	int sz = n * 2;
	t.resize(sz * 4);
	for (int i = 0; i < sz; i++) {
		upd(0, 0, sz, i, ar[i].second);
	}
	int pl = 0;
	int pr = sz - 1;
	int cur = 0;
	int val = t[0].mx;
	int cnt = 0;
	vector<int> ans(n + 1);
	for (; cur <= val; cur++) {
		ans[cur] = cnt;
	}
	for (int i = 0; i < n; i++) {
		cnt++;
		while (ar[pl].second != -1) {
			pl++;
		}
		while (ar[pr].second != 1) {
			pr--;
		}
		ar[pl].second = 1;
		ar[pr].second = -1;
		upd(0, 0, sz, pl, 1);
		upd(0, 0, sz, pr, -1);
		val = t[0].mx;
		for (; cur <= val; cur++) {
			ans[cur] = cnt;
		}
	}
	vector<int> qs(q);
	for (int i = 0; i < q; i++) {
		cin >> qs[i];
	}
	for (int i = 0; i < q; i++) {
		cout << ans[qs[i]] << ' ';
	}
	cout << '\n';
}
