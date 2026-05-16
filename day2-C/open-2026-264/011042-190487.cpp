#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

struct pair1 {
    int a;
    int t;
};

bool comp(pair1 a, pair1 b) {
    if (a.a == b.a) {
        return a.t < b.t;
    }
    return a.a < b.a;
}

bool comp1(pair1 a, pair1 b) {
    return a.a > b.a;
}

bool comp3(pair1 a, pair1 b) {
    return a.a + a.t * 2 > b.a + b.t * 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q; cin >> n >> q;
    vector<pair1> arr;
    vector<pair1> arr1;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        arr.push_back({a, b});
        arr1.push_back({a, -1});
        arr1.push_back({b, 1});
    }
    sort(arr1.begin(), arr1.end(), comp);
    vector<int> cnt;
    int cnt1 = 0;
    for (int i = 0; i < arr1.size(); i++) {
        if (arr1[i].t == -1) {
            cnt1++;
            cnt.push_back(cnt1);
        } else {
            cnt.push_back(cnt1);
            cnt1--;
        }
    }
    vector<int> ans(n + 1, n + 1);
    vector<pair1> otv;
    int cntl = 0;
    for (int i = 0; i < arr1.size() - 1; i++) {
        if (arr1[i].t == -1 && arr1[i + 1].t == 1) {
            int l = arr1[i].a;
            int r = arr1[i + 1].a;
            int cnt1 = cnt[i];
            int cntr = n - cnt1 - cntl;
            otv.push_back({cnt1, min(cntl, cntr)});
            // cntr = 0;
            // for (int i = 0; i < n; i++) {
            //     if (arr[i].a < l && arr[i].t < l) {
            //         cntl++;
            //     } else if (arr[i].a > r && arr[i].t > r) {
            //         cntr++;
            //     }
            // }
            // int x = min(cntl, cntr);
            // for (int j = 0; j < n + 1; j++) {
            //     if (j <= cnt1) {
            //         ans[j] = min(ans[j], 0);
            //     } else if (j <= cnt1 + 2 * x) {
            //         ans[j] = min(ans[j], (j - cnt1 + 1) / 2);
            //     } else {
            //         ans[j] = min(ans[j], j - cnt1 - 2 * x + x);
            //     }
            // }
        }
        if (arr1[i].t == 1) {
            cntl++;
        }
    }
    sort(otv.begin(), otv.end(), comp1);
    // for (auto el : otv) {
    //     // int l = otv[i].a;
    //     //     int r = arr1[i + 1].a;
    //         int cnt1 = el.a;
    //         int cntl = el.t;
    //         int cntr = n - cnt1 - cntl;
    //         // otv.push_back({cnt1, min(cntl, cntr)});
    //         // int cntr = 0;
    //         // for (int i = 0; i < n; i++) {
    //         //     if (arr[i].a < l && arr[i].t < l) {
    //         //         cntl++;
    //         //     } else if (arr[i].a > r && arr[i].t > r) {
    //         //         cntr++;
    //         //     }
    //         // }
    //         int x = min(cntl, cntr);
    //         for (int j = 0; j < n + 1; j++) {
    //             if (j <= cnt1) {
    //                 ans[j] = min(ans[j], 0);
    //             } else if (j <= cnt1 + 2 * x) {
    //                 ans[j] = min(ans[j], (j - cnt1 + 1) / 2);
    //             } else {
    //                 ans[j] = min(ans[j], j - cnt1 - 2 * x + x);
    //             }
    //         }
    // }
    int l = 0;
    for (int i = 0; i <= otv[0].a; i++) {
        ans[i] = 0;
    }
    l = 0;
    for (int i = 0; i < otv.size(); i++) {
        for (int j = l; j <= otv[i].a + otv[i].t * 2; j++) {
            ans[j] = min(ans[j], (j - otv[i].a + 1) / 2);
        }
        // l = max(l, otv[i].a + otv[i].t * 2 + 1);
    }
    int r = n;
    sort(otv.begin(), otv.end(), comp3);
    for (int i = 0; i < otv.size(); i++) {
        for (int j = r; j > otv[i].a + otv[i].t * 2; j--) {
            ans[j] = min(ans[j], j - otv[i].a - otv[i].t);
        }
        // r = min(r, otv[i].a + otv[i].t * 2);
    }
    while (q--) {
        int x; cin >> x;
        cout << max(ans[x], 0) << endl;
    }
}