/*
삼분탐색 에제. UVa 온라인 저지에서 가져온 문제인데 현재 그 사이트가 막혀있어 제출은 할 수 없었다.
달리기 길이를 maxDifference에서 삼분탐색을 통해 구하고
차이가 최대인 시간을 difference 함수에서 구해 답을 도출한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
const int MAX = 20;

int N;  //참가자 수
double track;  //트랙 길이
vector<double> runSpeed, cycleSpeed;  //뛰는 속도, 자전거 타는 속도

//달리기 구간의 길이가 run일때, i번 선수가 걸리는 시간
double time(int i, double run) {
    double cycle = track - run;
    return run / runSpeed[i] + cycle / cycleSpeed[i];
}

//달리기 구간 길이가 r일 때, others(r)-cheater(r) 를 반환한다.
double diff(double r) {
    int n = runSpeed.size();
    double cheater = time(n - 1, r);
    double others = time(0, r);
    for (int i = 1; i < n - 1; ++i)
        others = min(others, time(i, r));
    return others - cheater;
}

//diff() 함수의 최대치의 위치를 삼분 검색으로 계산한다.
double maxDifference() {
    double low = 0, high = track;
    for (int iter = 0; iter < 100; ++iter) {
        double a = (2 * low + high) / 3;
        double b = (low + 2 * high) / 3;

        if (diff(a) > diff(b))
            high = b;
        else
            low = a;
    }
    return (low + high) / 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> track) {
        cin >> N;

        //속도 입력
        for (int i = 0; i < N; ++i) {
            double run, cycle;
            cin >> run >> cycle;
            runSpeed.push_back(run);
            cycleSpeed.push_back(cycle);
        }

        double run = maxDifference();   //달린 길이
        double cycle = track - run;     //자전거 길이
        double timeDiff = diff(run);
        if (timeDiff >= 0.0) {
            cout << fixed;
            cout.precision(0);
            cout << "The cheater can win by " << (timeDiff * 3600);
            cout << fixed;
            cout.precision(2);
            cout << "seconds with r = " << run << "km and k = " << cycle << "km." << "\n";

        }
        else
            cout << "The cheater cannot win." << "\n";
    }

    return 0;
}
