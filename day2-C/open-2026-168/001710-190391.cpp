#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define F first
#define S second
#define Vector2 pair <int, int>
#define print(a) for (const auto& x : a) cout << x << ' ';

void solve()
{
	int n, q;
	cin >> n >> q;
	vector <Vector2> segs(n);
	vector <int> vs;
	for (auto& [x, y] : segs) {
		cin >> x >> y;
		vs.push_back(x);
		vs.push_back(y);
	}
	sort(all(vs));
	vs.erase(unique(all(vs)), vs.end());
	vector <int> curs;
	for (const auto& x : vs) {
		curs.push_back(2 * x);
		for (int i = 0; i < sz(vs) - 1; ++i) {
			curs.push_back(vs[i] + vs[i + 1]);
		}
	}
	vector <int> ans(n + 1, INT_MAX);
	ans[0] = 0;
	for (const auto& x : curs) {
		int l = 0, r = 0, s = 0;
		for (int i = 0; i < n; ++i) {
			if (2 * segs[i].S < x) {
				++l;
			} else if (2 * segs[i].F > x) {
				++r;
			} else {
				++s;
			}
		}
		for (int k = 1; k <= s + 2 * min(l, r); ++k) {
			int cnt = 0;
			if (k > s) {
				cnt = (k - s + 1) / 2;
			}
			ans[k] = min(ans[k], cnt);
		}
	}
	while (q--) {
		int k;
		cin >> k;
		cout << ans[k] << ' ';
	}
}

signed main()
{
	cin.tie(nullptr)->ios_base::sync_with_stdio(false);
	solve();
	return 0;
}