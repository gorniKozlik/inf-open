#include <bits/stdc++.h>

using namespace std;

struct event {
    int x;
    int t;
};

bool comp (event a, event b) {
    return a.x < b.x;
}
int main()
{
    int n, q;
    cin >> n >> q;
    vector <event> v;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        v.push_back({l, 1});
        v.push_back({r, -1});
    }
    sort(v.begin(), v.end(), comp);
    vector <pair <int, int>> s(n);
    int now_seg = 0;
    int prev_seg = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (v[i].t == 1) {
            now_seg++;
        } else {
            s.push_back({now_seg, min(n - prev_seg - now_seg, prev_seg)});
            now_seg--;
            prev_seg++;
        }
    }
    sort(s.begin(), s.end());
    reverse(s.begin(), s.end());
    stack <pair <int, int>> st;
    st.push(s[0]);
    for (int i = 1; i < n; ++i) {
        if (s[i].first + s[i].second > st.top().first + st.top().second) {
            st.push(s[i]);
        }
    }
    while (s.size()) {
        s.pop_back();
    }
    while (st.size()) {
        s.push_back(st.top());
        st.pop();
    }
    reverse(s.begin(), s.end());
    vector <int> ans(n, 0);
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < s.size() - 1 && s[j].first + i + min(s[j].second, i) < s[j + 1].first + i + min(s[j + 1].second, i)) {
            j++;
        }
        ans[i] = s[j].first + i + min(s[j].second, i);
    }
    while (q--) {
        int k;
        cin >> k;
        cout << lower_bound(ans.begin(), ans.end(), k) - ans.begin() << endl;
    }
    return 0;
}
