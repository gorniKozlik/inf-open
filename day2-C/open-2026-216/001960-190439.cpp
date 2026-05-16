#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>
#include <queue>
#include <unordered_map>
#include <set>
#include <deque>
#include <map>
#include <unordered_map>
using namespace std;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>>v;
	int l, r;
	for (int i = 0; i < n; i++) {
		cin >> l >> r;
		v.push_back({ l, 1 });
		v.push_back({ r, -1 });
	}
	sort(v.begin(), v.end());
	int t = 0;
	vector<vector<int>>g(2 * n);
	for (int i = 0; i < (n + n); i++) {
		if (v[i].second == 1) {
			g[i] = { t + 1, i - t, n+n-i-t-2};
			if (g[i][1] > g[i][2]) {
				g[i][1]--;
				g[i][2]++;
			}
			t++;
		}
		else {
			g[i] = { t, i - t, n + n - i - t };
			if (g[i][1] < g[i][2]) {
				g[i][1]++;
				g[i][2]--;
			}
			t--;
		}
	}
	vector<int>ans(n+1, 1e9);
	/*for (auto x : g) {
		cout << x[0] << " " << x[1] << " " << x[2] << "\n";
	}*/
	for (int i = 0; i < (n + n); i++) {
		g[i][1] = min(g[i][1], g[i][2]);
	}
	sort(g.begin(), g.end());
	for (int i = 1; i <= n; i++) {
		while ((g.size() > 0) && ((g.back()[0]+g.back()[1])<i)) {
			g.pop_back();
		}
		if (g.size() > 0) {
			if (i <= (g.back()[0])) {
				ans[i] = 0;
			}
			else {
				ans[i] = (i-g.back()[0] + 1) / 2;
			}
		}
	}
	for (int i = 0; i < q; i++) {
		cin >> l;
		cout << ans[l] << " ";
	}
}