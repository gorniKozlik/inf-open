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
    vector<int> ans(n+1, n+1);

    int max_p = 1;

    int balance = 0;
    int left_open = 0;
    int left_closed = 0;

    vector<vector<int>> add(n+2, vector<int>(0, 0));
    vector<vector<int>> del(n+2, vector<int>(0, 0));

    for (auto event: events){
        auto [coord, type] = event;
        if (type == -1){
            balance++;
            left_open++;
        } else {
            balance--;
            left_closed++;
        }

        for (int i = 1; i <= balance; ++i){
            ans[i] = 0;
        }

        int min_pairs = min(left_closed, n-left_open);

        add[balance].push_back(balance);
        del[balance+2*min_pairs+1].push_back(balance);
    }

    multiset<int> balances;

    for (int i = 1; i <= n; ++i){
        if (i <= max_p){
            ans[i] = 0;
        }

        for (int el: add[i]){
            balances.insert(el);
        }

        for (int el: del[i]){
            balances.erase(balances.find(el));
        }

        int max_balance = *(balances.rbegin());

        int rem = i-max_balance;

        ans[i] = rem/2+(rem%2);
    }

    for (int i = 0; i < q; ++i){
        int k;
        cin >> k;
        cout << ans[k] << " ";
    }

    return 0;
}