#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>

using namespace std;

vector<int> in;

struct tree {
	vector<int> nodes;
	void build(int v, int l, int r) {
		if (l == r - 1) {
			nodes[v] = in[l];
		}
		else {
			int mid = (l + r) >> 1;
			build((v << 1) + 1, l, mid);
			build((v << 1) + 2, mid, r);
			nodes[v] = max(nodes[(v << 1) + 1], nodes[(v << 1) + 2]);
		}
	}
	tree() {
		int n = in.size();
		nodes.assign(n << 2, 0);
		build(0, 0, n);
	}
	int get(int v, int l, int r, int xl, int xr) {
		if (l >= xl && r <= xr) {
			return nodes[v];
		}
		else if (r <= xl || l >= xr) {
			return 0;
		}
		else {
			int mid = (l + r) >> 1;
			return max(get((v << 1) + 1, l, mid, xl, xr), get((v << 1) + 2, mid, r, xl, xr));
		}
	}
};

int main() {
	int n, q, k; cin >> n >> q;
	vector<pair<int, int>> ci(n << 1);
	for (int i = 0; i < n; i++) {
		cin >> ci[i].first >> ci[i + n].first;
		ci[i].second = 1;
		ci[i + n].second = -1;
	}
	sort(ci.begin(), ci.end());
	n = (n << 1) - 1;
	int cnt = 0;
	in.assign(n, 0);
	for (int i = 0; i < n; i++) {
		cnt += ci[i].second;
		in[i] = cnt;
	}
	tree seg;
	for (int w = 0; w < q; w++) {
		cin >> k;
		int res = seg.get(0, 0, n, k - 1, n - k + 1);
		res = max(0, k - res);
		cout << ((res + 1) >> 1) << ' ';
	}
}
