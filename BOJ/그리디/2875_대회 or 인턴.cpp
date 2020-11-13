/*
처음에 풀 때는 남, 여 배열을 만들어서 모든 경우의 수를 저장해 그 중 적은 수가 있는 쪽이 팀이 되는 것으로 풀었다.
두번째 풀때는 배열을 사용하지 않고 모든 경우의 수를 따졌다.
다른 코드를 찾아보니 단순히 최대팀을 만들고 조건에 맞지 않으면 한팀을 깨는 식으로 풀었다.
*/

///////내가 푼 풀이
#include <iostream>

using namespace std;
int n, m, k;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    int max = 0;
    for (int i = 0; i <= k; i++) {
        int woman = n - i;
        int man = m - (k - i);

        //여학생은 2명이서 한팀
        woman /= 2;

        //둘 다 양수일때 더 적은 학생쪽으로 팀이 구성됨
        if (man > 0 && woman > 0) {
            if (man >= woman) {
                if (max < woman)
                    max = woman;
            }

            else {
                if (max < man)
                    max = man;
            }
        }

    }
    cout << max;

    return 0;
}



//////////////////////////////
/*
더 그리디에 맞는 방법인 것 같다.

주어진 남/여 학생으로 최대팀을 만들고 남은 값이 K보다 큰지 작은지를 판단하면 될것 같다.
큰 경우 그대로 최대팀수를 출력하면되고
작은 경우, 한팀을 깨부시면 될듯!
*/


#include <iostream>
using namespace std;

int main() {

    int N, M, K;
    cin >> N >> M >> K;

    int max = 0;
    while (N >= 2 && M >= 1) {
        N -= 2;
        M--;
        max++;
    }

    while (N + M < K) {
        N += 2;
        M++;
        max--;
    }

    cout << max << endl;

    return 0;
}