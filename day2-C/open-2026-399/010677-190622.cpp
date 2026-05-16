#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool cmp(int x, int y)
{
	return x > y;
}
struct eve
{
	int x;
	int t;
	int d;
};
bool cmp1(eve ev1, eve ev2)
{
	if (ev1.x != ev2.x)
		return ev1.x < ev2.x;
	return ev1.t < ev2.t;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> otr(n);
	vector<int> ls(n);
	vector<int> rs(n);
	vector<eve> ev;
	for (int i = 0; i < n; i++)
	{
		cin >> otr[i].first >> otr[i].second;
		ls[i] = otr[i].first;
		rs[i] = otr[i].second;
		ev.push_back({ ls[i], 1, 0 });
		ev.push_back({ rs[i], -1, 0 });
	}
	vector<int> ks(q);
	for (int i = 0; i < q; i++)
	{
		cin >> ks[i];
	}
	sort(rs.begin(), rs.end(), cmp);
	sort(ls.begin(), ls.end());
	/*for (auto el : ls)
		cout << el << " ";
	cout << "\n";
	for (auto el : rs)
		cout << el << " ";
	cout << "\n";*/
	while (ls.back() > rs.back())
	{
		int l = rs.back();
		int r = ls.back();
		rs.pop_back();
		ls.pop_back();
		ev.push_back({ l, 0, 1 });
		ev.push_back({ r, 0, -1 });
	}
	sort(ev.begin(), ev.end(), cmp1);
	/*for (auto el : ev)
	{
		cout << el.x << " " << el.t << " " << el.d << "\n";
	}*/
	int d = 0;
	int k = 0;
	vector<int> res(n+1, -1);
	for (auto el : ev)
	{
		//cout << el.x << " " << k << " " << d << "\n";
		//cout << el.t << " " << el.d << "\n";
		if (el.t == 1)
		{
			k++;
			//cout << "upd ";
			res[k] = max(res[k], d);
			//cout << res[k] << "\n";
		}
		if (el.t == -1)
		{
			k--;
		}
		if (el.t == 0)
		{
			d += el.d;
			res[k] = max(res[k], d);
		}
	}
	/*for (auto el : res)
		cout << el << " ";
	cout << "\n";*/
	int x = 0;
	vector<pair<int, int>> v;
	for (int i = 0; i <= n; i++)
	{
		if (res[i] != -1)
		{
			v.push_back({ i, res[i] * 2 });
			res[i] = 0;
			continue;
		}
		int cur_len = i - v.back().first;
		if (v.back().second < cur_len)
			v.pop_back();
		res[i] = (cur_len + 1) / 2;
	}
	for (int i = 0; i < ks.size(); i++)
	{
		cout << res[ks[i]] << " ";
	}
	getchar();
	getchar();
	return 0;
}

