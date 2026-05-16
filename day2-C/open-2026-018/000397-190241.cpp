#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>
#include <set>
#include <map>
#include <deque>
#include <stack>
#include <queue>
#include <array>
using namespace std;
using ll = long long;
using ld = long double;
#define endl '\n'
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q; cin >> n >> q; vector<int> coo; vector<array<int, 2>> qr;
	for (int i = 0; i < n; i++) {
		int l, r; cin >> l >> r; qr.push_back({ l, -1 }); qr.push_back({ r, 1 });
	}
	sort(qr.begin(), qr.end());
	vector<int> ans(n + 1, 1e9);
	int bal = 0, cl = 0;
	for (auto el : qr) {
		if (el[1] == -1) {
			bal++;
			ans[bal] = min(ans[bal], 0);
			int x = n - cl - bal;
			for (int i = 1; i <= min(x, cl); i++) {
				ans[bal + i] = min(ans[bal + i * 2 - 1], i); ans[bal + i + 1] = min(ans[bal + i * 2], i);
			}
			if (x != cl) ans[bal + min(x, cl) * 2 + 1] = min(ans[bal + min(x, cl) * 2 + 1], min(x, cl) + 1);
		} else {
			ans[bal] = min(ans[bal], 0);
			int x = n - cl - bal;
			for (int i = 1; i <= min(x, cl); i++) {
				ans[bal + i] = min(ans[bal + i * 2 - 1], i); ans[bal + i + 1] = min(ans[bal + i * 2], i);
			}
			if (x != cl) ans[bal + min(x, cl) * 2 + 1] = min(ans[bal + min(x, cl) * 2 + 1], min(x, cl) + 1);
			bal--; cl++;
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		ans[i] = min(ans[i], ans[i + 1]);
	}
	while (q--) {
		int p; cin >> p; cout << ans[p] << endl;
	}
	return 0;
}
