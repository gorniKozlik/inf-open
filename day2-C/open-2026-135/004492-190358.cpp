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
//bool check(int l1, int r1, int l2, int r2) {
//	return min(r1, r2) >= max(l1, l2);
//}
int scan(set <pair <int, int>>& s) {
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
	set <pair <int, int>> s;
	for (auto el : a) s.insert(el);
	int last = scan(s);
	vector <int> ans(n + 1);
	int past = 0;
	while (true) {
		pair <int, int> bl = { MOD, MOD }, br = { -MOD, -MOD };
		for (auto [l, r] : s) {
			if (bl.first > l) bl = { l, r };
			if (br.second < r) br = { l, r };
		}
		s.erase(bl);
		s.erase(br);
		if (bl != br) {
			s.insert({ min(bl.second, br.first), max(bl.second, br.first) });
			past++;
		}
		int cur = past + scan(s);
		for (int i = last + 1; i <= cur; ++i) ans[i] = ans[last] + 1;
		last = cur;
		if (cur == n) break;
		if (s.empty()) break;
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
