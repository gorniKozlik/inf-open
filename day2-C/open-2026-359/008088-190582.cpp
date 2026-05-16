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
	vector<pair<ll, ll>> v(2 * n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first>>a[i].second;
		v[2 * i].first = a[i].first;
		v[2 * i].second = 1;
		v[2 * i + 1].first = a[i].second;
		v[2 * i + 1].second = -1;
	}
	sort(v.begin(), v.end());
	ll count = 0, mcount = 0, cur1 = 0, cur2 = 0;
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
	ll cnt = 0;
	vector<ll> ct, mct, ct1;
	
	ll count2 = 0, count3 = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (v[i].second == 1) {
			count3++;
		}
		count2 += v[i].second;
		if (count2 == mcount) {
			ct.push_back(count3-count2);
			mct.push_back(n-count3);
			ct1.push_back(2*count3-count2-n);
		}
	}
	ll j2 = MOD, j1 = 0;
	for (int i = 0; i < ct1.size(); i++) {
		if (abs(ct1[i]) < j2) {
			j2 = abs(ct1[i]);
			j1 = i;
		}
	}
	ll cnt3 = ct[j1];
	ll cnt2 = n - cnt3 - mcount;
	ll p = min(cnt3, cnt2);
	vector<ll> k(n+1);
	for (int i = mcount + 1; i <= n; i++) {
		if (i <= 2 * p + mcount) {
			if ((i - mcount) % 2) {
				k[i] = k[i - 1] + 1;
			}
			else {
				k[i] = k[i - 1];
			}
		}
		else {
			k[i] = k[i - 1] + 1;
		}
	}
	for (int i = 0; i < q; i++) {
		int lk;
		cin >> lk;
		cout << k[lk]<<" ";
		
	}
}

