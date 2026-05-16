#ifdef LOCAL
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <string>
#include <ctime>
#include <climits>
#include <iomanip>
#include <numeric>
#include <random>
#include <array>
#include <bitset>
#include <unordered_map>
#include <unordered_set>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define int long long

using ll = long long;
using ld = long double;
using namespace std;

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& p) {
	in >> p.first >> p.second;
	return in;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2>& p) {
	out << p.first << " " << p.second;
	return out;
}

template<typename T>
istream& operator>>(istream& in, vector<T>& a) {
	for (auto& el : a) {
		in >> el;
	}
	return in;
}

template<typename T>
ostream& operator<<(ostream& out, vector<T>& a) {
	if (a.empty()) return out;
	out << a[0];
	for (int i = 1; i < (int)a.size(); i++) {
		out << " " << a[i];
	}
	return out;
}

const int INF32 = 1e9;
const ll INF64 = 1e18;

void solve() {
	int n, q;
	cin >> n >> q;
	vector<int> left(2 * n);
	vector<int> right(2 * n);
	vector<int> dists;
	vector<pair<int, int>> otrs;
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		dists.push_back(l);
		dists.push_back(r);
		otrs.push_back({ l, r });
	}
	sort(dists.begin(), dists.end());
	for (int i = 0; i < n; i++) {
		int l = lower_bound(dists.begin(), dists.end(), otrs[i].first) - dists.begin();
		int r = lower_bound(dists.begin(), dists.end(), otrs[i].second) - dists.begin();
		left[l] = 1;
		right[r] = 1;
	}
	vector<int> pref(2 * n);
	pref[0] = right[0];
	for (int i = 1; i < 2 * n; i++) {
		pref[i] = pref[i - 1] + right[i];
	}
	vector<int> suf(2 * n);
	suf[2 * n - 1] = left[2 * n - 1];
	for (int i = 2 * n - 2; i >= 0; i--) {
		suf[i] = suf[i + 1] + left[i];
	}
	vector<int> ans(n + 1, INF64);
	int mxhave = -INF64;
	vector<vector<pair<int, int>>> open(n + 1);
	vector<vector<pair<int, int>>> close(n + 1);
	for (int i = 0; i < 2 * n; i++) {
		int have = n;
		int v1 = 0, v2 = 0;
		if (i != 0) {
			have -= pref[i - 1];
			v1 = pref[i - 1];
		}
		if (i != 2 * n - 1) {
			have -= suf[i + 1];
			v2 = suf[i + 1];
		}
		mxhave = max(mxhave, have);
		int l = have;
		int r = have + min(v1, v2) * 2;
		open[l].push_back({ l, i });
		if (r != n) {
			close[r + 1].push_back({ l, i });
		}
		have--;
		v1++;
		v2++;
		l = have;
		r = min(n, have + min(v1, v2) * 2);
		open[l].push_back({ l, i });
		if (r != n) {
			close[r + 1].push_back({ l, i });
		}
	}
	set<pair<int, int>> vals;
	for (int i = 0; i <= n; i++) {
		for (auto& p : open[i]) {
			vals.insert(p);
		}
		for (auto& p : close[i]) {
			vals.erase(p);
		}
		if (!vals.empty()) {
			ans[i] = vals.rbegin()->first;
		}
	}
	for (int tt = 1; tt <= q; tt++) {
		int k;
		cin >> k;
		if (k <= mxhave) {
			cout << 0 << " ";
		} else {
			cout << (k - ans[k] + 1) / 2 << " ";
		}
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
	ld start_time = clock();
#endif
	solve();
#ifdef LOCAL
	ld finish_time = clock();
	cout << "\n" << "finished in: " << (finish_time - start_time) / CLOCKS_PER_SEC;
#endif
	return 0;
}