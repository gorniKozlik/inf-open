#include <bits/stdc++.h>

using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;

    cin >> n >> q;

    vector<pair<int, int>> segments;
    vector<pair<int, int>> events;

    for (int i = 0; i < n; ++i){
        int l, r;
        cin >> l >> r;
        segments.emplace_back(l, r);
        events.push_back({l, -1});
        events.push_back({r, 1});
    }

    sort(events.begin(), events.end());

    int max_p = 1;

    int balance = 0;

    for (auto event: events){
        auto [coord, type] = event;
        if (type == -1){
            balance++;
        } else {
            balance--;
        }

        max_p = max(max_p, balance);
    }

    int ans = (n-max_p)/2+1;

    cout << ans;

    return 0;
}