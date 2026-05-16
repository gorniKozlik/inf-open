#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <array>
#include <deque>
using namespace std;
using ll = long long;
#define all(x) x.begin(),x.end()

const ll INF = 1e9 + 7, M = 1e9 + 7, LG = 17, MAXN = 2e5;
vector<pair<int,int>> s;
int get1(int k) {
	while (!s.empty() and s.back().second < k)
	{
		s.pop_back();
	}
	return s.back().first;
}


void solve() {
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> sa;
	for (int i = 0; i < n; i++)
	{
		int l, r;
		cin >> l >> r;
		sa.emplace_back(l, 1);
		sa.emplace_back(r, -1);
	}
	sort(all(sa));
	int cnt = 0, op = 0;
	vector<pair<int, int>> hl;
	for (auto i : sa) {
		if (i.second == 1) {
			op += 1;
		}
		
		int cl = n - op - cnt, val = op + min(cl, cnt) * 2;
		if ((cl > cnt and i.second == -1) or (cnt > cl and i.second == 1)) {
			++val;
		}
		hl.emplace_back(op, val);
		if (i.second == -1) {
			op -= 1;
			cnt += 1;
		}
	}
	sort(all(hl));
	vector<pair<int,int>> k(q);
	vector<int> ans(q);
	for (int i = 0; i < q; i++)
	{
		cin >> k[i].first;
		k[i].second = i;
	}
	sort(all(k));
	int ind = 0;
	for (int i = 0; i < q; i++)
	{
		while (ind < hl.size() and hl[ind].first <= k[i].first)
		{
			s.push_back(hl[ind++]);
		}
		int val = get1(k[i].first);
		ans[k[i].second] = (k[i].first - val + 1) / 2;
	}
	for (int i = 0; i < q; i++)
	{
		cout << ans[i] << ' ';
	}
}

int main()
{
#ifdef _DEBUG
	freopen("in.txt", "r", stdin);
#endif // _DEBUG
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
}

