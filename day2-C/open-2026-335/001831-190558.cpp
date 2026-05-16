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
constexpr int MAXN = 500;
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
		int rgt = n - lft - cur;
		for (int i = 0; i <= n; i++) {
			if (i <= cur)
				ans[i] = 0;
			else if (i <= cur + 2 * min(rgt, lft)) {
				ans[i] = min(ans[i], min(rgt, lft));
			} else {
				ans[i] = min(ans[i], min(rgt, lft) + n - cur - 2 * min(rgt, lft));
			}
		}
	}
	for (int i = 0; i < q; i++) {
		int x;
		cin >> x;
		assert(ans[x] < 1e9);
		cout << ans[x] << " ";
	}
	return 0;
}
