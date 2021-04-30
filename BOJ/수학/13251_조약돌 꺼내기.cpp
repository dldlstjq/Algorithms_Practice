/*
조합의 수를 구하는 것이 아니라 확률을 구한다고 해서 당황스러웠다.
전체 조약돌 수 중에서 K개 뽑았을 때 같은 조약돌일 확률을 구하면 되는 단순한 문제인데
식이 생각이 잘 안났다.
그래도 아직까지는 수학적인 머리가 남아있는 것 같아 수월하게 해결했다.
*/

#include <iostream> 
using namespace std;

const int MAX = 50 + 1;
double rock[MAX];
double M, K;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> M;
    double total = 0;
    for (int i = 0; i < M; ++i) {
        cin >> rock[i];
        total += rock[i];
    }

    cin >> K;

    double ret = 0;

    cout.precision(10);
    //조약돌 색이 1개이거나 1개만 뽑으면 무조건 확률은 1
    if (M == 1 || K == 1)
        cout << 1.0;
    else {
        //확률 계산. 전체개수에서 k번만큼 특정 색 뽑는 확률 더한다.
        //예시: (7/18)*(6/17)*(5/16) 이렇게 확률을 구해서 더한다.
        for (int i = 0; i < M; ++i) {
            double tmp_rock = rock[i];
            double tmp_total = total;
            double probability = 1;
            for (int j = 0; j < K; ++j) {
                probability *= (tmp_rock--) / (tmp_total--);
            }
            ret += probability;
        }
        cout << ret;
    }

    return 0;
}