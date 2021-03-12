#include <bits/stdc++.h>
using namespace std;
#define _GLIBCXX_DEBUG
typedef long long ll;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(v) v.begin(), v.end()
template<class T>bool chmax(T& a, const T& b) { if (a<b) { a=b; return 1;} return 0;}
template<class T>bool chmin(T& a, const T& b) { if (b<a) { a=b; return 1;} return 0;}

const int MAX = 10000;
int n;
vector<vector<int>> xyr;
bool flgs[MAX][MAX];
vector<vector<int>> res;
vector<vector<int>> ans;

void paintOut(int tl_x, int tl_y, int br_x, int br_y) {
    for (int i = tl_y; i <= br_y; ++i) {
        for (int j = tl_x; j <= br_x; ++j) {
            flgs[i][j] = true;
        }
    }
}

int area(int tl_x, int tl_y, int br_x, int br_y) {
    int x = abs(tl_x - br_x), y = abs(tl_y - br_y);
    return (x + 1) * (y + 1);
}

double score() {
    double ret = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> tmp = res[xyr[i][0]];
        double a = area(tmp[0], tmp[1], tmp[2]-1, tmp[3]-1);
        ret += 1 - (1 - a / xyr[i][3]) * (1 - a / xyr[i][3]);
    }
    ret /= n;
    return ret;
}

vector<int> explore(int sx, int sy, int r, int dx, int dy) {
    bool x_flag = true, y_flag = true;
    int first_x = sx, first_y = sy;

    while (x_flag || y_flag) {

        if (first_x + dx == -1 || first_x + dx == MAX) x_flag = false;
        if (area(first_x + dx, first_y, sx, sy) > r) {
            x_flag = false;
        }
        if (x_flag) {
            for (int i = min(first_y, sy); i <= max(first_y, sy); ++i) {
                if (flgs[i][first_x + dx]) {
                    x_flag = false;
                    break;
                }
            }
            if (x_flag) first_x += dx;
        }

        if (first_y + dy == -1 || first_y + dy == MAX) y_flag = false;
        if (area(first_x, first_y + dy, sx, sy) > r) {
            y_flag = false;
        }
        if (y_flag) {
            for (int i = min(first_x, sx); i <= max(first_x, sx); ++i) {
                if (flgs[first_y + dy][i]) {
                    y_flag = false;
                    break;
                }
            }
            if (y_flag) first_y += dy;
        }
    }

    x_flag = true, y_flag = true;
    int second_x = sx, second_y = sy;
    dx *= -1, dy *= -1;

    while (x_flag || y_flag) {

        if (second_x + dx == -1 || second_x + dx == MAX) x_flag = false;
        if (area(first_x, first_y, second_x + dx, second_y) > r) {
            x_flag = false;
        }
        if (x_flag) {
            for (int i = min(first_y, second_y); i <= max(first_y, second_y); ++i) {
                if (flgs[i][second_x + dx]) {
                    x_flag = false;
                    break;
                }
            }
            if (x_flag) second_x += dx;
        }

        if (second_y + dy == -1 || second_y + dy == MAX) y_flag = false;
        if (area(first_x, first_y, second_x, second_y + dy) > r) {
            y_flag = false;
        }
        if (y_flag) {
            for (int i = min(first_x, second_x); i <= max(first_x, second_x); ++i) {
                if (flgs[second_y + dy][i]) {
                    y_flag = false;
                    break;
                }
            }
        }
        if (y_flag) second_y += dy;
    }
    return {first_x, first_y, second_x, second_y};
}

void solve() {
    int dx[] = {1, 1, 0, 0};
    int dy[] = {1, 0, 1, 0};
    int dxx[] = {1, 1, -1, -1};
    int dyy[] = {1, -1, 1, -1};
    double highest = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (j == 0) {
                sort(all(xyr), [&](auto& a, auto& b)
                {return dx[i]*a[1] + (MAX-a[1])*(dx[i]^1) + dy[i]*a[2] + (MAX-a[2])*(dy[i]^1)
                > dx[i]*b[1] + (MAX-b[1])*(dx[i]^1) + dy[i]*b[2] + (MAX-b[2])*(dy[i]^1);});
            }
            else if (j == 1) {
                sort(all(xyr), [&](auto& a, auto& b)
                {return dx[i]*a[1] + (MAX-a[1])*(dx[i]^1) + dy[i]*a[2] + (MAX-a[2])*(dy[i]^1) + a[3]/5000
                > dx[i]*b[1] + (MAX-b[1])*(dx[i]^1) + dy[i]*b[2] + (MAX-b[2])*(dy[i]^1) + b[3]/5000;});
            }
            else {
                sort(all(xyr), [&](auto& a, auto& b)
                {return dx[i]*a[1] + (MAX-a[1])*(dx[i]^1) + dy[i]*a[2] + (MAX-a[2])*(dy[i]^1) + a[3]/10000
                > dx[i]*b[1] + (MAX-b[1])*(dx[i]^1) + dy[i]*b[2] + (MAX-b[2])*(dy[i]^1) + b[3]/10000;});
            }

            memset(flgs, false, sizeof(flgs));
            rep(k, n) flgs[xyr[k][2]][xyr[k][1]] = true;
            rep(k, n) {
                int x = xyr[k][1], y = xyr[k][2], r = xyr[k][3];
                vector<int> coordinate = explore(x, y, r, dxx[i], dyy[i]);
                int big_x = max(coordinate[0], coordinate[2]);
                int big_y = max(coordinate[1], coordinate[3]);
                int small_x = min(coordinate[0], coordinate[2]);
                int small_y = min(coordinate[1], coordinate[3]);
                paintOut(small_x, small_y, big_x, big_y);
                res[xyr[k][0]] = {small_x, small_y, big_x + 1, big_y + 1};
            }
            if (chmax(highest, score())) {
                rep(k, n) ans[k] = res[k];
            }
        }
    }

    rep(i, n) {
        rep(j, 4) {
            if (j) cout << " ";
            cout << ans[i][j];
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
    ans.resize(n, vector<int>(3));
    res.resize(n, vector<int>(3));
    solve();
}