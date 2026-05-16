#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>
#include <iomanip>
#define int long long
using namespace std;

int comp(vector<int>& T, int x) {
	return lower_bound(T.begin(), T.end(), x) - T.begin();
}


signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q; cin >> n >> q;
	vector<int> a;
	vector<int> l(n);
	vector<int> r(n);
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
		a.push_back(l[i]);
		a.push_back(r[i]);
	}
	sort(a.begin(), a.end());
	vector<bool> fl(2 * n);
	vector<int> pl(2 * n + 10);
	vector<int> mn(2 * n + 10);
	for (int i = 0; i < n; i++) {
		l[i] = comp(a, l[i]);
		r[i] = comp(a, r[i]);
		pl[l[i]]++;
		mn[r[i] + 1]--;
		if (r[i] - l[i] == 1) {
			fl[r[i]] = 1;
		}
	}
	int L = 0, R = 2 * n;
	int cnt = 0;
	vector<int> res(n + 1, 1e18);
	for (int i = 0; i < 2 * n; i++) {
		cnt += pl[i];
		cnt += mn[i];
		R--;
		int lt = L - cnt + 1, rt = R - cnt + 1;
		if (pl[i] == 1) {
			rt--;
		}
		else {
			lt--;
		}
		int f = min(rt, lt);
		res[cnt + f] = min(res[cnt + f], f / 2);
		res[cnt + f + 1] = min(res[cnt + f + 1], f / 2 + 1);
		L++;

	}
	for (int i = res.size() - 3; i >= 0; i--) {
		res[i] = min(res[i], res[i + 2] - 1);
		res[i] = max(0ll, res[i]);
	}
	while (q--) {
		int x; cin >> x;
		cout << res[x] << ' ';
	}
}