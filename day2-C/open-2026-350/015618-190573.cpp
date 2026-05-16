#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int q, n; cin >> n >> q;
    vector<pair<int, int>> pull;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        pull.push_back(make_pair(a, 1));
        pull.push_back(make_pair(b, -1));
    }
    sort(pull.begin(), pull.end());
    vector<int> K(q);
    for (int i = 0; i < q; ++i) cin >> K[i];
    int cnt = 0;
    for (int i = 0; i < n; ++i){
        if (pull[i].second == -1) ++cnt;
    }
    cout << cnt << '\n';
}
