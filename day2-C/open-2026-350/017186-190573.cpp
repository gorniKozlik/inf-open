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
    int t = *max_element(K.begin(), K.end());
    vector<int> T(t + 1, -1);
    int a = 0;
    int b = 0;
    for (int i = 0; i < n * 2; ++i){
        if (i == n) b = a;
        a += pull[i].second;
        T[a] = 0;
    }
    bool flag = false;
    for (int i = n; i > 0; --i){
        if (flag) T[i] = 0;
        if (T[i] == 0) flag = true;
    }
    int k = 0;
    for (int i = 0; i < T.size(); ++i){
        if (T[i] != -1) continue;
        bool flag = true;
        ++k;
        T[i] = k;
        for (int j = 1; j < n - 1; ++j){
            if (pull[j].second == -1 and pull[j - 1].second == 1 and pull[j + 1].second == 1){
                T[i + 1] = k;
                pull[j].second = 1;
                flag = false;
                break;
            }
        }
        if (flag){
            for (int j = 1; j < n; ++j){
                if (pull[j].second == -1){
                    pull[j].second = 1;
                    break;
                }
            }
        }
    }
    for (int h : K){
        cout << T[h] << '\n';
    }
}
