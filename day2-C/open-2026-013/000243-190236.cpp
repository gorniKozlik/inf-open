#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>

using namespace std;
using ll = long long;

signed main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n, q;
	cin >> n >> q;
	vector<int> l(n), r(n), d;
	for (int i = 0; i < n; ++i) {
		cin >> l[i] >> r[i];
		d.push_back(l[i]);
		d.push_back(r[i]);
	}
	sort(d.begin(), d.end());
	d.resize(unique(d.begin(), d.end()) - d.begin());
	for (int i = 0; i < n; ++i) {
		l[i] = lower_bound(d.begin(), d.end(), l[i]) - d.begin();
		r[i] = lower_bound(d.begin(), d.end(), r[i]) - d.begin();
	}

	vector<int> pr(2 * n), pl(2 * n);
	for (int i = 0; i < n; ++i) {
		pr[r[i]] += 1;
		pl[l[i]] += 1;
	}
	for (int i = 1; i < 2 * n; ++i) {
		pr[i] += pr[i - 1];
	}
	for (int i = 2 * n - 2; i >= 0; --i) {
		pl[i] += pl[i + 1];
	}

	vector<int> rs(n + 1, 1e9);
	rs[0] = 0;
	for (int i = 0; i + 1 < 2 * n; ++i) {
		int cl = pr[i];
		int cr = pl[i + 1];
		int f = n - cl - cr;
		for (int j = f; j <= f + 2 * min(cl, cr); ++j) {
			rs[j] = min(rs[j], (j - f + 1) / 2);
		}
	}

	for (int i = 0; i < q; ++i) {
		int k;
		cin >> k;
		cout << rs[k] << ' ';
	}

	return 0;
}
