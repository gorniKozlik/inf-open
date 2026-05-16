#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int q, n; cin >> q >> n;
    vector<pair<int, int>> pull(2 * n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        pull.push_back(make_pair(a, 1));
        pull.push_back(make_pair(b, -1));
    }
    sort(pull.begin(), pull.end());
    vector<int> A(n);
    int cnt = 0;
    for (int i = 0; i < n; ++i){
        if (pull[i].second == -1) ++cnt;
    }
    cout << cnt;
}
