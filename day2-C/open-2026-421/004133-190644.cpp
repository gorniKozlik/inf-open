
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <algorithm>
#include <iomanip>
#include <queue>


using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

int inf = 1000000000;

struct seg_tree {
	int n = 0;
	int t_s = 0;
	vector<int> val;
	vector<int> t;

	void tmp(int e) {
		if (e < t_s / 2 - 1) {
			tmp(e * 2 + 1);
			tmp(e * 2 + 2);
			t[e] = max(t[e * 2 + 1], t[e * 2 + 2]);
		}
	}
	void init() {
		t.resize(int(pow(2, ceil(log2(n)) + 1)));
		t_s = t.size();

		for (int i = 0; i < n; i++) {
			t[i + t_s / 2 - 1] = val[i];
		}

		tmp(0);
	}

	int f_lr(int l, int r, int lb, int rb, int e = 0) {
		if (l >= rb or r <= lb) {
			return 0;
		}
		else if (l <= lb and r >= rb) {
			return t[e];
		}
		else {
			return max(f_lr(l, r, lb, (rb + lb) / 2, e * 2 + 1),
				f_lr(l, r, (rb + lb) / 2, rb, e * 2 + 2));
		}
	}

	void upp(int id, int lb, int rb, int val, int e = 0) {
		if (lb == rb - 1) {
			t[e] += val;
			return;
		}
		else if (id < (lb + rb) / 2) {
			t[e] += val;
			upp(id, lb, (lb + rb) / 2, val, e * 2 + 1);
		}
		else {
			t[e] += val;
			upp(id, (lb + rb) / 2, rb, val, e * 2 + 2);
		}
	}

	int f_n0(int val) {
		int ans = 0;

		int e = 0;
		while (e < t_s / 2 - 1) {
			if (ans + t[e * 2 + 1] < val) {
				ans += t[e * 2 + 1];
				e = e * 2 + 2;
			}
			else {
				e = e * 2 + 1;
			}
		}

		return  e - (t_s / 2 - 1);// первый элемент сумма префикса до которого равна или больше искомой
	}
};
int f_p(vector<int>& a, int e) {
	if (a[e] != -1) {
		e = a[e];
	}
	return 0;
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	//_________________________________________

	int n, q; cin >> n >> q;

	map<int, pii> a;

	vector<int> c;
	vector<int> o;

	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		a[x].first++;
		a[y].second++;
	}


	vector<pii> b;

	for (auto i : a) {
		int cc = i.second.second;
		while (cc--) {
			c.push_back(b.size());
		}
		int oc = i.second.first;
		while (oc--) {
			o.push_back(b.size());
		}
		b.push_back(i.second);
	}

	sort(c.rbegin(), c.rend());
	sort(o.begin(), o.end());

	seg_tree k;
	k.n = b.size();
	k.val.resize(k.n);

	int cou = 0;

	for (int i = 0; i < b.size(); i++) {
		cou += b[i].first;
		k.val[i] = cou;
		cou -= b[i].second;
	}
	k.init();

	int mx = k.f_lr(0, k.n, 0, k.t_s / 2);
	vector<int> ans = { mx };

	cou = 0;

	while (c.back() < o.back()) {
		mx = max(mx, 
				max(
					k.f_lr(c.back() + 1, o.back(), 0, k.t_s / 2) + cou * 2 + 2, 
					max(
						k.val[c.back()] + cou * 2 + 1, 
						k.val[o.back()] + cou * 2 + 1
					)
				)
			);
		cou++;
		ans.push_back(mx);
		c.pop_back();
		o.pop_back();
	}

	while (q--) {
		int x; cin >> x;
		cout << lower_bound(ans.begin(), ans.end(), x) - ans.begin() << ' ';
	}





	//_________________________________________

	return 0;
}