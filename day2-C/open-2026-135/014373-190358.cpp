#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;
#define ll long long
#define ld long double
const ll INF = 1e18;
const int MOD = 1e9 + 7;
int scan(vector <pair <int, int>> s) {
	vector <pair <int, int>> v;
	for (auto [l, r] : s) {
		v.push_back({ l, 0 });
		v.push_back({ r, 1 });
	}
	sort(v.begin(), v.end());
	int cur = 0, res = 0;
	for (auto [x, t] : v) {
		if (t == 0) cur++;
		else cur--;
		res = max(res, cur);
	}
	return res;
}
void solve() {
	int n, q; cin >> n >> q;
	vector <pair <int, int>> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
	vector <int> qv(q); for (int i = 0; i < q; ++i) cin >> qv[i];
	int last = scan(a);
	vector <int> ans(n + 1);
	int sum = 0;
	while (true) {
		int mx = -1;
		int bi = 0, bj = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				auto [l1, r1] = a[i];
				auto [l2, r2] = a[j];
				vector <int> c = { l1, l2, r1, r2 };
				sort(c.begin(), c.end());
				a[i] = { c[0], c[3] };
				a[j] = { c[1], c[2] };
				int cur = scan(a);
				if (cur > mx) {
					mx = max(mx, cur);
					bi = i;
					bj = j;
				}
				a[i] = { l1, r1 };
				a[j] = { l2, r2 };
			} 
		}
		if (mx == -1) break;
		sum++;
		for (int i = last + 1; i <= mx; ++i) ans[i] = sum;
		last = mx;
		auto [l1, r1] = a[bi];
		auto [l2, r2] = a[bj];
		vector <int> c = { l1, l2, r1, r2 };
		sort(c.begin(), c.end());
		a[bi] = { c[0], c[3] };
		a[bj] = { c[1], c[2] };
		if (mx == n) break;
	}
	for (auto el : qv) cout << ans[el] << " ";
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int TESTS = 1; //cin >> TESTS;
	while (TESTS--) solve();
}
