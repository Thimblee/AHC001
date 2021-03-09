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

void paintOut(int x, int y, int size) {
    x -= size, y -= size;
    size = 2 * size + 1;
    for (int i = y; i < y + size; ++i) {
        for (int j = x; j < x + size; ++j) {
            flgs[i][j] = 1;
        }
    }
}

int square(int sx, int sy, int r) {
    --sx, --sy; // upper left
    int len = 3;
    while (len*len <= r) {
        if (sy < 0 || sy + len >= MAX) return len/2 - 1;
        if (sx < 0 || sx + len >= MAX) return len/2 - 1;

        rep(i, len) if (flgs[sy+i][sx]) return len/2 - 1;
        rep(i, len) if (flgs[sy+len-1][sx+i]) return len/2 - 1;
        rep(i, len) if (flgs[sy+i][sx+len-1]) return len/2 - 1;
        rep(i, len) if (flgs[sy][sx+i]) return len/2 - 1;

        --sx, --sy, len += 2;
    }
    return len/2 - 1;
}

void solve() {
    rep(i, n) flgs[xyr[i][2]][xyr[i][1]] = 1;
    sort(all(xyr), [](auto& x, auto& y){return x[3] < y[3];});
    rep(i, n) {
        int x = xyr[i][1], y = xyr[i][2], r = xyr[i][3];
        flgs[y][x] = 0;
        int size = square(x, y, r);
        paintOut(x, y, size);
        res[xyr[i][0]] = {x-size, y-size, x+1+size, y+1+size};
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