/*
삼분검색을 써서 푸는 문제.
백준 문제로 접할때도 삼분탐색이 뭔말인지 몰랐는데 기하로 접근하니까 더 어려웠다.
풀려고 했었는데 일주일을 붙잡고 있어도 못 풀것 같아 해답을 바로 봤다.
나중에 기하부분까지 이해가 되면 그때 다시 풀어보면 좋을 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


struct point {
    double y, x;
};

//입력에 주어진 볼록 다각형
vector<point> hull1, hull2;

//위 껍질에 속하는 선분들과 아래 껍질에 속하는 선분들
vector<pair<point, point> > upper, lower;
//hull이 반시계방향으로 주어지므로, 인접한 두 점에 대해 x가
//증가하는 방향이면 아래쪽 껍질, x가 감소하는 방향이면 위쪽 껍질이다.
void decompose(const vector <point >& hull) {
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        if (hull[i].x < hull[(i + 1) % n].x)
            lower.push_back({ hull[i], hull[(i + 1) % n] });
        else if (hull[i].x > hull[(i + 1) % n].x)
            upper.push_back({ hull[i], hull[(i + 1) % n] });
    }
}

//[a.x, b.x] 구간 안에 x가 포함되나 확인한다.
bool between(const point& a, const point& b, double x) {
    return (a.x <= x && x <= b.x) || (b.x <= x && x <= a.x);
}

//(a,b) 선분과 주어진 위치의 수직선이 교차하는 위치를 반환한다.
double at(const point& a, const point& b, double x) {
    double dy = b.y - a.y, dx = b.x - a.x;
    return a.y + dy * (x - a.x) / dx;
}

//두 다각형의 교집합을 수직선으로 잘랐을 때 단면의 길이를 반환한다.
double vertical(double x) {
    double minUp = 1e20, maxLow = -1e20;
    //위 껍질의 선분을 순회하며 최소 y 좌표를 찾는다.
    for (int i = 0; i < upper.size(); ++i) {
        if (between(upper[i].first, upper[i].second, x))
            minUp = min(minUp, at(upper[i].first, upper[i].second, x));
    }

    //아래 껍질의 선분을 순회하며 최소 y 좌표를 찾는다.
    for (int i = 0; i < lower.size(); ++i) {
        if (between(lower[i].first, lower[i].second, x))
            maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
    }

    return minUp - maxLow;
}

double minX(vector<point>& p) {
    double result = p[0].x;
    for (int i = 1; i < p.size(); i++)
        result = min(result, p[i].x);
    return result;
}

double maxX(vector<point>& p) {
    double result = p[0].x;
    for (int i = 1; i < p.size(); i++)
        result = max(result, p[i].x);
    return result;
}

double solve() {
    //수직선이 두 다각형을 모두 만나는 x좌표의 범위를 구한다.
    double lo = max(minX(hull1), minX(hull2));
    double hi = min(maxX(hull1), maxX(hull2));

    //예외처리: 두 다각형이 아예 겹치지 않는 경우
    if (hi < lo) return 0;
    //삼분검색
    for (int iter = 0; iter < 100; ++iter) {
        double aab = (lo * 2 + hi) / 3.0;
        double abb = (lo + hi * 2) / 3.0;

        if (vertical(aab) < vertical(abb))
            lo = aab;
        else
            hi = abb;
    }
    return max(0.0, vertical(hi));
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int C;
    cin >> C;

    while (C--) {
        int n, m;
        cin >> n >> m;

        hull1.clear();
        hull2.clear();
        //첫번째 다각형 꼭짓점
        for (int i = 0; i < n; ++i) {
            point temp;
            cin >> temp.x >> temp.y;
            hull1.push_back(temp);
        }

        //두번째 다각형 꼭짓점
        for (int i = 0; i < m; ++i) {
            point temp;
            cin >> temp.x >> temp.y;
            hull2.push_back(temp);
        }

        lower.clear();
        upper.clear();

        //위 아래 껍질로 분류
        decompose(hull1);
        decompose(hull2);
        double result = solve();
        if (result <= 0)
            cout << "0.000000" << "\n";
        else {
            cout << fixed;
            cout.precision(10);
            cout << result << "\n";
        }
    }

    return 0;
}