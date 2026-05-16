// consoleapp1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma GCC target ("avx2", "bmi", "popcnt", "lzcnt")
#pragma optimize ("Ofast")
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using ll = long long;
using namespace std;
//vector<vector<int>> edges;
//vector<ll> visited;
//vector<ll> depth;
ll MOD = 998244353;
//void dfs(int v, int h) {
//	depth[v] = h;
//	visited[v] = 1;
//	for (int i = 0; i < edges[v].size(); i++) {
//		if (!visited[edges[v][i]]) {
//			dfs(edges[v][i], h + 1);
//		}
//	}
//}
ll binpow(int n, int k) {
	ll res = 1, a = n;
	while (k) {
		if (k & 1) {
			res *= a;
			res %= MOD;
		}
		a *= a;
		a %= MOD;
		k >>= 1;
	}
	return res;
}
int main() {
	ll n, q;
	cin >> n >> q;
	vector<pair<ll, ll>> a(n);
	vector<pair<int, int>> v(2 * n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first>>a[i].second;
		v[2 * i].first = a[i].first;
		v[2 * i].second = 1;
		v[2 * i + 1].first = a[i].second;
		v[2 * i + 1].second = -1;
	}
	sort(v.begin(), v.end());
	int count = 0, mcount = 0, cur1 = 0, cur2 = 0;
	pair<ll, ll> c, mc;
	for (int i = 0; i < 2 * n; i++) {
		if (v[i].second == -1) {
			cur1++;
		}
		count += v[i].second;
		if (count == 1 && v[i].second == 1) {
			c.first = v[i].first;
		}
		if (count == 0 && v[i].second == -1) {
			c.second = v[i].first;
		}
		/*if (count == 0 && cur1 > cur2 && ) {
			cur2 = cur1;
		}
*/
		if (count > mcount)
		{
			mcount = count;
			mc.first = c.first;
			mc.second = c.second;
		}
		
		}
	int cnt = 0;
	vector<pair<ll, ll>> ct, mct;
	for (int i = 0; i < 2 * n; i++) {

	}
	for (int i = 0; i < 2 * n; i++) {
		if (v[i].first >= mc.first) {
			break;
		}
		if (v[i].second == 1) {
			cnt++;
		}
	}
	int cnt2 = n - cnt - mcount;
	int p = min(cnt, cnt2);
	vector<ll> k(q);
	for (int i = 0; i < q; i++) {
		cin >> k[i];
		if (k[i] <= mcount) {
			cout << "0 ";
		}
		else if (k[i] <= p) {
			cout << (k[i] - mcount) / 2 + (k[i]-mcount)%2<< " ";
		}
		else {
			cout << (p - mcount) / 2 + (p - mcount) % 2 +(k[i]-p)<< " ";
		}
	}
}

