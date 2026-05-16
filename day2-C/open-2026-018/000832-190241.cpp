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
	int n, q; cin >> n >> q; vector<int> coo; vector<array<int, 3>> qr;
	for (int i = 0; i < n; i++) {
		int l, r; cin >> l >> r; qr.push_back({ l, -1, i + 1 }); qr.push_back({ r, 1, i + 1 });
	}
	sort(qr.begin(), qr.end());
	vector<int> ans(n + 1, 1e9);
	int bal = 0, cl = 0;
	multiset<int> ms; vector<array<int, 3>> qr1;
	for (auto el : qr) {
		if (el[1] == -1) {
			bal++;
			int x = n - cl - bal;
			int l = bal, r = bal + min(x, cl) * 2 + (x != cl);
			qr1.push_back({ l, -1, r }); qr1.push_back({ r, 1, l });
		} else {
			int x = n - cl - bal;
			int l = bal, r = bal + min(x, cl) * 2 + (x != cl);
			qr1.push_back({ l, -1, r }); qr1.push_back({ r, 1, l });
			bal--; cl++;
		}
	}
	sort(qr1.begin(), qr1.end());
	int it = 0;
	for (int i = 1; i <= n; i++) {
		while (it < qr1.size() && qr1[it][0] == i && qr1[it][1] == -1) {
			ms.insert(qr1[it][0]); it++;
		}
		if (ms.size()) {
			ans[i] = (i - *prev(ms.end()) + 1) / 2;
		}
		while (it < qr1.size() && qr1[it][0] == i && qr1[it][1] == 1) {
			ms.erase(ms.find(qr1[it][2])); it++;
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
