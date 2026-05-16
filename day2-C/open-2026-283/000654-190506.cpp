#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

mt19937 gen;

int rnd(int l, int r) {
	return uniform_int_distribution<int>(l, r)(gen);
}


signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cout.precision(30);

	int n, q;
	cin >> n >> q;

	vector<pair<int, int>> e;

	for (int i = 0; i < n; ++i) {
		int l, r;
		cin >> l >> r;
		e.emplace_back(l, 1);
		e.emplace_back(r, -1);
	}

	sort(e.begin(), e.end());

	vector<pair<int, int>> e2;

	int cnt = 0;
	for (int i = 0; i < 2 * n; ++i) {
		cnt += e[i].second;

		int add = min((i + 1 - cnt) / 2, (2 * n - i - 1 - cnt) / 2);

		e2.emplace_back(cnt, 1);
		e2.emplace_back(cnt + add * 2, -cnt - 1);
	}

	for (int i = 0; i <= n; ++i) {
		e2.emplace_back(i, 0);
	}

	sort(e2.begin(), e2.end(), [&](pair<int, int> x, pair<int, int>y) {
		if (x.first != y.first) return x.first < y.first;
		return x.second > y.second;
		});
	multiset<int> s[2];
	s[0].insert(-1e9);
	s[1].insert(-1e9);
	vector<int> ans(n + 1);
	for (pair<int, int> p : e2) {
		if (p.second == 0) {
			ans[p.first] = (p.first - *--s[p.first % 2].end()) / 2;
		}
		else if (p.second == 1) {
			s[p.first % 2].insert(p.first);
		}
		else {
			s[p.first % 2].erase(s[p.first % 2].find(-p.second - 1));
		}
	}

	for (int i = 0; i < q; ++i) {
		int k;
		cin >> k;
		cout << ans[k] << '\n';
	}
}
