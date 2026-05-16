#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
#define ll long long
#define al(a) a.begin(), a.end()
#define con continue

ll dstr(int i, int j, vector<int>& y) {
	return abs(y[i] - y[j]) / 2 + min(y[i], y[j]);
}
ll dsto(int i, int j, vector<int>& y) {
	return abs(y[i] - y[j]) / 2;
}


ll mxdst(vector<int>& y, vector<int>& lr, int i, ll m) {
	ll mxno = -1;
	ll mxye = -1;
	int n = size(y);
	for (int j = 0; j < n; j++) {
		if (j == i) {
			con;
		}
		if (lr[i] != lr[j]) {
			mxno = max(mxno, dstr(i, j, y));
		}
		else {
			mxye = max(mxye, dsto(i, j, y));
		}
	}
	return min(m - mxye, mxno);
}

int main(){
	int t;
	cin >> t;
	int n, m;
	cin >> n >> m;
	vector<int> y(n);
	ll cntod = 0, cntev = 0;
	set<int> ys;
	for (int i = 0; i < n; i++) {
		cin >> y[i];
		y[i]--;
		ys.insert(y[i]);
		if (y[i] % 2 == 0) {
			cntod++;
		}
		else {
			cntev++;
		}
	}
	vector<int> lr(n, 0);
	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		if (c == 'R') {
			lr[i] = 1;
		}
	}

	ll ok = (cntod == n || cntev == n ? 1 : 0);
	if (!ok) {
		cout << "No";
		return 0;
	}
	cout << "Yes\n";
	if (t == 2) {
		ll ans2 = 0;
		for (int i = 0; i < n; i++) {
			ans2 = max(ans2, mxdst(y, lr, i, m));
		}
		cout << ans2;
		return 0;
	}
	
}