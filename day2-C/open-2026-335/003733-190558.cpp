#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <set>
#include <map>
#include <cassert>
#include <queue>
#include <deque>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<pi> a(n);
	vector<int> sj;
	for (auto &[l, r] : a) {
		cin >> l >> r;
		sj.push_back(l);
		sj.push_back(r);
	}
	sort(sj.begin(), sj.end());
	sj.erase(unique(sj.begin(), sj.end()), sj.end());
	vector<pi> ev;
	for (auto &[l, r] : a) {
		l = lower_bound(sj.begin(), sj.end(), l) - sj.begin();
		r = lower_bound(sj.begin(), sj.end(), r) - sj.begin();
		ev.push_back({l, 0});
		ev.push_back({r + 1, -1});
	}
	sort(ev.begin(), ev.end());
	vector<int> ans(n + 1, 1e9);
	vector<pi> temp;
	vector<pi> temp1;
	int cur = 0;
	int lft = 0;
	for (int i = 0; i < ev.size(); i++) {
		auto [x, t] = ev[i];
		if (t == 0)
			cur++;
		else {
			lft++;
			cur--;
		}
		if (i == ev.size() - 1 || ev[i + 1].first != x) {
			int rgt = n - lft - cur;
			ans[cur] = 0;
			temp.push_back({cur, cur + 2 * min(rgt, lft) + 1});
		}
	}
	sort(temp.begin(), temp.end(), greater<pi>());
	vector<pi> ln;
	int maxr = -1;
	for (auto [l, r] : temp) {
		if (r > maxr) {
			ln.push_back({l, r});
			maxr = r;
		}
	}
	for (int i = 0; i <= n; i++) {
		int l = -1, r = ln.size();
		while (r - l > 1) {
			int m = (l + r) >> 1;
			if (i <= ln[m].second)
				r = m;
			else
				l = m;
		}
		if (r != ln.size()) {
			ans[i] = min(ans[i], max(0, (i - ln[r].first + 1) / 2));
		}
	}
	int mn = 1e9;
	for (int i = 0; i <= n; i++) {
		ans[i] = min(ans[i], max(0,i + mn));
		mn = min(mn, ans[i] + i);
	}
	for (int i = n - 1; i >= 0; i--)
		ans[i] = min(ans[i], ans[i + 1]);
	for (int i = 0; i < q; i++) {
		int x;
		cin >> x;
		cout << ans[x] << " ";
	}
	return 0;
}
