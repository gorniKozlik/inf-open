#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
ostream& operator<<(ostream& out, vector<T> v) {
	for (T it : v) {
		out << it << ' ';
	}
	out << '\n';
	return out;
}

#define ll long long
#define pii pair<int, int>

const int MAX = 500'005;
const int LG = 24;
const int MOD = 998'244'353;

pii s[MAX];

struct evt {
	int i;
	int t;
};
int main()
{
	int n, q;
	cin >> n >> q;

	vector<evt> v;
	for (int i = 0; i < n; i++) {
		cin >> s[i].first >> s[i].second;
		v.push_back({ s[i].first, 1 });
		v.push_back({ s[i].first, -1 });
	}
	sort(v.begin(), v.end(), [](evt a, evt b) { return a.i < b.i; });
	int mx = 0;
	int cur = 0;
	for (evt e : v) {
		cur += e.t;
		mx = max(mx, cur);
	}
	int k;
	for (int i = 0; i < q; i++) {
		cin >> k;
		cout << max(0, (k - mx / 2))<< ' ';
	}

}


