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

struct seg {
	int l, r;
};


bool OK(seg a, seg b) {
	if (a.l == b.l) {
		return a.r < b.r;
	}
	return a.l < b.l;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, q; cin >> n >> q;

	vector<seg> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].l >> a[i].r;
	}
	vector<int> cnt;
	sort(a.begin(), a.end(), OK);
	set<pair<int, int>> R;
	for (int i = 0; i < n; i++) {
		if (R.size() == 0) {
			cnt.push_back(1);
			R.insert({ a[i].r, cnt.size() - 1 });
			continue;
		}
		pair<int, int> temp = { a[i].l, -1ll };
		auto it = lower_bound(R.begin(), R.end(), temp);
		if (it == R.begin()) {
			cnt.push_back(1);
			R.insert({ a[i].r, cnt.size() - 1 });
		}
		else {
			it--;
			int e = (*it).second;
			cnt[e]++;
			R.erase(it);
			R.insert({ a[i].r, e });
		}
	}
	int ch2 = 0, ch1 = 0;
	ch2 += ch1 / 2;
	ch1 %= 2;
	for (auto now : cnt) {
		ch2 += (now - 1) / 2;
		if (now % 2 == 0) {
			ch1++;
		}
	}
	int st = cnt.size();
	while (q--) {
		int x; cin >> x;
		if (x <= st) {
			cout << 0 << '\n';
		}
		else {
			x -= st;
			if (x - ch2 * 2 <= 0) {
				cout << (x + 1) / 2 << '\n';
			}
			else {
				x -= ch2 * 2;
				cout << ch2 + x << '\n';
			}
		}
	}
}