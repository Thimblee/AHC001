#include <bits/stdc++.h>
using namespace std;
#define _GLIBCXX_DEBUG
typedef long long ll;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(v) v.begin(), v.end()
template<class T>bool chmax(T& a, const T& b) { if (a<b) { a=b; return 1;} return 0;}
template<class T>bool chmin(T& a, const T& b) { if (b<a) { a=b; return 1;} return 0;}

using pint = pair<int, int>;
const int MAX = 10000;
int n;
vector<vector<int>> xyr;
bool flgs[MAX][MAX];
vector<vector<int>> res;

void paintOut(int tl_x, int tl_y, int br_x, int br_y) {
    for (int i = tl_y; i <= br_y; ++i) {
        for (int j = tl_x; j <= br_x; ++j) {
            flgs[i][j] = true;
        }
    }
}

vector<int> topLeft(int sx, int sy, int r) {

    bool left_f = true, top_f = true;
    int now_row = sy, now_col = sx;

    while (left_f || top_f) {

        if (now_col == 0) left_f = false;
        if (left_f) {
            for (int i = now_row; i <= sy; ++i) {
                if (flgs[i][now_col-1]) {
                    left_f = false;
                    break;
                }
            }
            if (left_f) now_col--;
        }

        if (now_row == 0) top_f = false;
        if (top_f) {
            for (int i = now_col; i <= sx; ++i) {
                if (flgs[now_row-1][i]) {
                    top_f = false;
                    break;
                }
            }
            if (top_f) now_row--;
        }
    }
    return {now_col, now_row};
}

void solve() {
    rep(i, n) flgs[xyr[i][2]][xyr[i][1]] = true;
    sort(all(xyr), [](auto& a, auto& b){return a[1] + a[2] < b[1] + b[2];});
    rep(i, n) {
        int x = xyr[i][1], y = xyr[i][2], r = xyr[i][3];
        vector<int> top_left = topLeft(x, y, r);
        paintOut(top_left[0], top_left[1], x, y);
        res[xyr[i][0]] = {top_left[0]+1, top_left[1]+1, x+1, y+1};
    }

    rep(i, n) {
        rep(j, 4) {
            if (j) cout << " ";
            cout << res[i][j];
        }
        cout << endl;
    }
}

int main() {
    cin >> n;
    xyr.resize(n, vector<int>(4));
    rep(i, n) {
        xyr[i][0] = i;
        cin >> xyr[i][1] >> xyr[i][2] >> xyr[i][3];
    }
    res.resize(n, vector<int>(3));
    solve();
}