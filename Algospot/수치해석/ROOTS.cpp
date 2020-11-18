/*
첫 알고스팟 문제.
수치해석을 배우긴 배웠는데 1년전에 배운거라 기억이 잘 안난다.
방정식 계산때 근의 공식에서 2*a 에 괄호를 안 쳐줘서 오답 해결에 애를 먹었다.

런타임 에러가 많이 나서 방법을 찾지 못했는데 N, C 입력할 때 예외처리 부분에서 런타임 에러가 났었다.
다른 곳에서 에러가 난 줄 알고 해결에 시간이 많이 걸렸다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//방정식의 해의 절대 값은 L 이하여야만 한다
const double L = 10;
int N;  //방정식 차수

//단일 변수 다항식 p의 계수가 주어질 때 미분한 결과 p`의 계수를 반환
vector<double> differentiate(const vector<double>& poly) {
    int n = poly.size() - 1;
    vector<double> diff_poly;
    for (int i = 0; i < n; i++) {
        diff_poly.push_back(poly[i] * (n - i));
    }
    return diff_poly;
}

//1차 혹은 2차 방정식을 푼다
vector<double> solveNaive(const vector<double>& poly) {
    int n = poly.size() - 1;
    vector<double> result;
    if (n == 1) {
        result.push_back((-1) * (poly[1] / poly[0]));
    }
    else if (n == 2) {
        double a = poly[0], b = poly[1], c = poly[2];
        result.push_back((-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));
        result.push_back((-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a));

    }
    sort(result.begin(), result.end());
    return result;
}

//다항식 f(x)의 계수 poly가 주어질 때 f(x0)를 반환
double evaluate(const vector<double>& poly, double x0) {
    double result = 0;
    int n = poly.size() - 1;
    for (int i = 0; i <= n; i++) {
        result += pow(x0, n - i) * poly[i];
    }
    return result;
}

//방정식 sum(poly[i]*x^i)=0의 근을 반환한다.
vector<double> solve(const vector<double>& poly) {
    int n = poly.size() - 1;

    //기저 사례: 2차 이하의 방정식들은 풀 수 있다.
    if (n <= 2)
        return solveNaive(poly);

    //방정식을 미분해서 n-1차 방정식을 얻는다
    vector<double> derivative = differentiate(poly);
    // 미분한 방정식에 대한 극점을 재귀를 통하여 구한다
    vector<double> sols = solve(derivative);

    //이 극점들 사이를 하나하나 검사하며 근이 있나 확인한다.
    //초기 극점과 마지막 극점은 비교대상이 없으므로 ±L과 비교
    sols.insert(sols.begin(), -L - 1);
    sols.insert(sols.end(), L + 1);

    vector<double> ret;
    for (int i = 0; i + 1 < sols.size(); i++) {
        //인접하는 극점
        double x1 = sols[i], x2 = sols[i + 1];
        double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);

        //f(x1)과 f(x2)의 부호가 같은 경우 답은 없다.
        if ((y1 * y2) > 0)
            continue;
        //불변 조건:f(x1) <= 0 <= f(x2)
        if (y1 > y2) {
            swap(y1, y2);
            swap(x1, x2);
        }
        // while 이 아닌 최대 100 정도의 for문으로 이분법을 돌리는 것은
        // 이분법 과정에서 무한루프를 방지할 수 있다.
        for (int iter = 0; iter < 100; ++iter) {
            double mx = (x1 + x2) / 2;
            //y는 x를 대입하여 계산
            double my = evaluate(poly, mx);

            if (y1 * my > 0) {
                y1 = my;
                x1 = mx;
            }
            else {
                y2 = my;
                x2 = mx;
            }
        }
        ret.push_back((x1 + x2) / 2);
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // 입력의 첫 줄에는 테스트 케이스의 수 C(C<=50)가 주어집니다.
    // 각 테스트 케이스의 첫 줄에는 방정식의 차수 n(2 <= n <= 5)이 주어지고,
    // 그 다음 줄에 n+1개의 실수로 방정식의 차수가 고차항부터 주어집니다.

    int C;
    cin >> C;

    while (C--) {
        cin >> N;

        vector<double> poly;
        for (int i = 0; i < N + 1; ++i) {
            double coef;
            cin >> coef;
            poly.push_back(coef);
        }

        // 각 테스트 케이스마다 n개의 실수로 오름차순으로 정렬된 방정식의 해를 출력합니다.
        // 방정식의 해는 모두 다르다고 가정해도 좋습니다.
        // 10 - 8 이하의 상대 / 절대 오차가 있는 답은 정답으로 처리됩니다.

        vector<double> ans = solve(poly);
        //소수점 자리수를 12자리로 고정
        cout << fixed;
        cout.precision(12);
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}