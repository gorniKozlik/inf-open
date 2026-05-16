#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<pair<int, int>> otr(n);
	for (int i = 0; i < n; i++)
		cin >> otr[i].first >> otr[i].second;
	vector<int> ks(q);
	for (int i = 0; i < q; i++)
	{
		cin >> ks[i];
		cout << ks[i] - 1 << " ";
	}
	return 0;
}