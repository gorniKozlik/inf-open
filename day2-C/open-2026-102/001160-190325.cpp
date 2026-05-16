#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <random>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;
using ll = long long;
using ld = long double;

const int inf = 1e9 + 10;

int main()
{
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> lr(n);
	set<int> st0;
	map<int, int> mp;
	for (int i = 0; i < n; i++) {
		cin >> lr[i].first >> lr[i].second;
		st0.insert(lr[i].first);
		st0.insert(lr[i].second);
	}
	int cnt = 0;
	for (auto x : st0)
		mp[x] = cnt++;
	for (int i = 0; i < n; i++) {
		lr[i].first = mp[lr[i].first];
		lr[i].second = mp[lr[i].second];
	}

	vector<int> cntl(n * 2), cntr(n * 2);
	sort(lr.begin(), lr.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		return a.second < b.second;
	});
	int pos = 0;
	for (int i = 0; i < n * 2; i++) {
		while (pos < n && lr[pos].second <= i)
			pos++;
		cntl[i] = pos;
	}
	sort(lr.rbegin(), lr.rend(), [](const pair<int, int>& a, const pair<int, int>& b) {
		return a.first < b.first;
		});
	pos = 0;
	for (int i = n * 2 - 1; i >= 0; i--) {
		while (pos < n && lr[pos].first > i)
			pos++;
		cntr[i] = pos;
	}

	vector<pair<int, int>> x(n * 2);
	vector<int> a(n * 2);
	for (int i = 0; i < n * 2; i++) {
		a[i] = min(cntl[i], cntr[i]);
		x[i] = { n - cntl[i] - cntr[i], i };
	}
	sort(x.begin(), x.end(), [&](const pair<int, int>& p1, const pair<int, int>& p2) {
		return a[p1.second] < a[p2.second];
	});
	set<pair<int, int>> st1, st2;
	for (auto p : x)
		st1.insert(p);
	
	pos = 0;
	int pos_ans = 1;
	int v2 = -inf;
	vector<int> ans(n + 1, -1);
	for (int k = 0; k <= n; k++) {
		while (pos < n * 2 && a[x[pos].second] <= k) {
			const int i = x[pos].second;
			st1.erase({ n - cntl[i] - cntr[i], i });
			v2 = max(v2, n - cntl[i] - cntr[i] + a[i] * 2);
			//st2.insert({ n - cntl[pos] - cntr[pos] + a[pos], pos });
			pos++;
		}
		int v1 = -inf;
		if (!st1.empty())
			v1 = (--st1.end())->first + k * 2;
		int v = max(v1, v2);
		while (pos_ans <= min(n, v)) {
			ans[pos_ans]= k;
			pos_ans++;
		}
	}

	vector<int> ans2(m);
	for (int i = 0; i < m; i++) {
		int k;
		cin >> k;
		ans2[i] = ans[k];
	}
	for (auto x : ans2)
		cout << x << '\n';
}
