#include<vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <deque>

using namespace std;
#define int long long

const int inf = 1e18;

const int mxn = 2e5 + 7;
const int  lgx = 22;
int t[mxn];
int mod = 998244353;
int lg[mxn];
int st[lgx];

void print(vector<int>& a)
{
	for (auto x : a)
		cout << x << " ";
	cout << "\n";
}


int maxx(int l, int r,vector<vector<int>> &sp)
{
	int ln = r - l + 1;
	return max(sp[lg[ln]][l], sp[lg[ln]][r - st[lg[ln]] + 1]);
}

int sm(int r)
{
	int res = 0;
	for (;r > 0; r -= r & (-r))
		res += t[r];
	return res;
}

int sm(int l, int r)
{
	return sm(r) - sm(l - 1);
}

void add(int i, int x)
{
	for (; i < mxn; i += i & (-i))
		t[i] += x;
}

struct node 
{
	int add, sm;
};

struct Tree
{
	int len = 1;
	vector<node> tr;

	void init(int n)
	{
		while (len < n)
			len *= 2;
		tr.assign(2 * len - 1, { 0, -1 });
	}

	void push(int x, int ln)
	{
		if (tr[x].add != -1)
		{
			tr[2 * x + 1].sm = tr[x].add * ln / 2;
			tr[2 * x + 1].add = tr[x].add;

			tr[2 * x + 2].sm = tr[x].add * ln / 2;
			tr[2 * x + 2].add = tr[x].add ;

			tr[x].sm = tr[x].add * ln;
			tr[x].add = -1;
		}
	}

	void add(int x, int lx, int rx, int l, int r, int v)
	{
		
		if (l <= lx && rx <= r)
		{
			tr[x].add = v;
			tr[x].sm = v * (rx - lx + 1);
			return;
		}

		if (l > rx || r < lx)
		{
			return;
		}
		push(x, rx - lx + 1);
		int m = (lx + rx) / 2;
		add(2 * x + 1, lx, m, l, r, v);
		add(2 * x + 2, m + 1, rx, l, r, v);
		tr[x].sm = tr[2 * x + 1].sm + tr[2 * x + 2].sm;
	}

	int sm(int x, int lx, int rx, int l, int r)
	{
		if (l <= lx && rx <= r)
		{
			return tr[x].sm;
		}

		if (l > rx || r < lx)
		{
			return 0 ;
		}
		push(x, rx - lx + 1);
		int m = (lx + rx) / 2;
		int s1 = sm(2 * x + 1, lx, m, l, r);
		int s2 = sm(2 * x + 2, m + 1, rx, l, r);
		return s1 + s2;
	}

	void add(int l, int r, int v)
	{
		add(0, 0, len - 1, l, r, v);
	}

	int sm(int l, int r)
	{
		return sm(0, 0, len - 1, l, r);
	}
};



int pw(int a, int b)
{
	if (b == 0)
		return 1;
	if (b % 2 == 0)
	{
		int q = pw(a, b / 2);
		return q * q % mod;
	}
	int q = pw(a, b - 1);
	return q * a % mod;
}

vector<int> ob(vector<int> p)
{
	vector<int> q(p.size(), 0);
	for (int i = 0; i < p.size(); i++)
		q[p[i] - 1] = i + 1;
	return q;
}

vector<int> pr(vector<int> p)
{
	vector<int> q(p.size(), 0);
	for (int i = 0; i < p.size(); i++)
		q[i] = q.size() - p[i] + 1;
	return q;
}


int sc(vector<int> a)
{
	int ans = 0;
	for (int i = 0; i < a.size(); i++)
		ans = (pw(a[i], i + 1) + ans) % mod;
	return  ans;
}


signed main()
{
	int n, qx;
	cin >> n >> qx;
	vector<pair<int ,int>> a(n);
	vector<int> z(n);
	for (int i = 0; i < n; i++)
		cin >> a[i].first >> a[i].second;
	for (int i = 0; i < qx; i++)
		cin >> z[i];
	vector<int> ans(n + 1, inf);

	vector<pair<int, int>> sc;
	for (int i = 0; i < n; i++)
	{
		sc.push_back({a[i].first, -1 });
		sc.push_back({ a[i].second, 1 });
	}

	sort(sc.begin(), sc.end());
	int c = 0;
	int pc = 0;
	pair<int, int> mxn = { -1, -1 };
	vector<int> pr(sc.size());
	for (int i = 0; i < sc.size(); i++)
	{

		c -= sc[i].second;
		int chl = 0;
		if (sc[i].second == 1)
		{
			pc++;
			chl = 1;
		}
		int b = min(pc - chl, n - c - pc);
		pair<int, int> rt = { c, b };
		if (rt > mxn)
		{
			mxn = rt;
		}
	}
	
	c = mxn.first;
	int  b = mxn.second;

	vector<int> ax(n + 1);
	for (int j = 1; j <= c; j++)
	{
		ax[j] = 0;
	}

	
	//cout << c << " " << b <<  "\n"; 
	int q = 1;
	for (int j = c + 1; j <= c + b * 2; j += 2)
	{
		ax[j] = q;
		ax[j + 1] = q;
		q += 1;
	}
	for (int j = c + b * 2 + 1; j <= n; j++)
	{
		ax[j] = q;
		q++;
	}
	//print(ax);
	for (auto x : z)
	{
		cout << ax[x] << " ";
	}

}
