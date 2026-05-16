#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <stack>
#include <deque>
#include <numeric>
#include <iomanip>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int INF = 2e9;
void solve() {
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> points(n);
	vector<pair<int, int>> events;
	for (int i = 0; i < n; i++) {
		cin >> points[i].first >> points[i].second;
		events.push_back({ points[i].first, 0 });
		events.push_back({ points[i].second, 1 });
	}
	vector<int> k(q);
	vector<pair<int, int>> ks(q);
	vector<int> ans(q, INF);
	vector<int> can(n + 100, INF);
	for (int i = 0; i < q; i++) {
		cin >> k[i];
		ks[i] = { k[i], i };
	}
	sort(ks.begin(), ks.end());
	sort(k.begin(), k.end());
	sort(events.begin(), events.end());
	int mn = 0;
	int cnt = 0;
	int elapsed = 0;
	for (auto i : events) {
		if (i.second == 0) {
			cnt++;
			can[cnt] = 0;
			mn = min(elapsed, n - elapsed - cnt);
			can[cnt + mn * 2] = min(can[cnt + mn * 2], mn);
		}
		else {
			//cout << i.first << " " << i.second << endl;
			cnt--;
			elapsed++;
		}
	}
	/*for (auto i : can) {
		cout << i << " ";
	} cout << endl;*/
	for (int i = n + 99; i > 0; i--) {
		//cout << can[i] << " " << can[i - 1] << " " << i << endl;
		can[i - 1] = min(can[i - 1], can[i]);
		if (i != 1 && can[i] != 0 && can[i] != INF) {
			//cout << can[i - 2] << " " << can[i] - 1 << endl;
			can[i - 2] = min(can[i - 2], can[i] - 1);
		}
	}
	for (int i = 0; i < n + 99; i++) {
		can[i + 1] = min(can[i + 1], can[i] + 1);
	}
	for (auto i : ks) {
		ans[i.second] = can[i.first];
	}
	for (auto i : ans) {
		cout << i << " ";
	}
}
signed main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	//cout << fixed << setprecision(6);
	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}
}
/*

*/