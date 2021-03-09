#include <bits/stdc++.h>
using namespace std;
#define _GLIBCXX_DEBUG
typedef long long ll;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define all(v) v.begin(), v.end()
template<class T>bool chmax(T& a, const T& b) { if (a<b) { a=b; return 1;} return 0;}
template<class T>bool chmin(T& a, const T& b) { if (b<a) { a=b; return 1;} return 0;}

const int MAX = 10000;
int n, a, b, c, d;
int flgs[MAX][MAX];

int main() {
    memset(flgs, 0, sizeof(flgs));
    cin >> n;
    while (n--) {
        cin >> a >> b >> c >> d;
        for (int i = a; i <= c; ++i) {
            for (int j = b; j <= d; ++j) {
                flgs[i][j]++;
            }
        }
    }

    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            if (flgs[i][j] > 1) {
                cout << i << " " << j << endl;
            }
        }
    }
}