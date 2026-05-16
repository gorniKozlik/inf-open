// трепещи, Пэрри утконос
// я изобрёл камбек-инатор

// плохому комбисту и Бабин мешает

// на контесте я придумал замечательный стишок
// очень долго в задачу я пихал корешок
// раз пишок и два пишок
// раздаётся на весь зал истерический смешок

// про хромого короля
// расскажу вам сказку
// чекер был настолько пьян
// что пустился в пляску

// спасибо бате за такую наследственность
// большие баллы - большая ответственность

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353, maxn = 1e6, inf = 1e9 + 7;
mt19937 rnd(55);

int tme[maxn], a[maxn];
int n, q;

struct query {
    int x, type, idx;
};

query pts[maxn];
int l[maxn], r[maxn], cap[maxn], ans[maxn];

bool cmp(query & a, query & b) {
    return (a.x < b.x || (a.x == b.x && a.type < b.type));
}

void sixsevenbrainsrotted() {
    cin >> n >> q;
    for (int i = 0; i < n; i++)  {
        cin >> l[i] >> r[i];

    }
    for (int i = 0; i < n; i++) {
        l[i] = l[i], r[i] = r[i];
        pts[i * 2] = {l[i], 0, i};
        pts[i * 2 + 1] = {r[i], 1, i};
    }
    //капасити = открытые но не закрытые + min(кол-во закрытых, ещё не открытые)
    sort(pts, pts + n * 2, cmp);
    int cur = 0, closed = 0;
    for (int i = 0; i < n * 2; i++) {
        //cout << pts[i].x << " ";
        if (pts[i].type == 0) {
            cur++;
            ans[i] = cur;
        } else {
            ans[i] = cur;
            cur--;
            closed++;
        }
        cap[i] = min(i, n * 2 - i);
    }
    /*cout << '\n';
    for (int i = 0; i < n * 2; i++) {
        cout << ans[i] << " " << cap[i] << "\n";
    }
    cout << "OK\n";
    */
    while (q--) {
        int ki;
        cin >> ki;
        int mxans = 0;
        for (int i = 0; i < n * 2; i++) {
            if (cap[i] >= ki) {
                mxans =  max(ans[i], mxans);
            }
        }
        cout << max((ki - mxans + 1) / 2, 0) << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tests = 1;
    while (tests--) {
        sixsevenbrainsrotted();
    }
}
