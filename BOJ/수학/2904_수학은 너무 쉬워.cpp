/*
[산술의 기본 정리] 모든 양의 정수는 소인수 분해를 갖는다.
즉 모든 양의 정수는 소수의 곱으로 표현할 수 있습니다.
이는 마찬가지로 공약수 또한 소수의 곱으로 표현할 수 있습니다.

이러한 성질을 이용하면 결국 문제에서 원하는 모든 수에 적힌 최대공약수의 최댓값을 구하려면 
각각의 점수를 소인수 분해했을 때 공통적으로 들어있는 소수의 곱이 최대가 되면 됩니다.

[두 수 A와 B를 고르고, A를 나눌 수 있는 소수 X를 고른다. 그 다음, A를 지우고 A/X를 쓰고, B를 지우고 B×X를 쓴다.]
위 문제 조건을 잘 생각해보면 어떤 한 점수를 소인수 분해해서 나온 소수들 중 하나를 떼서(나눠서) 다른 점수에 붙일 수(곱해서) 있습니다.
결국 모든 점수들의 최대 공약수가 최대가 되도록 조건을 이용해서 구하는 방법은 각각의 점수를 소인수 분해 한 다음 소수들을 골고루 분배하면 됩니다.

문제의 테스트 케이스 예제를 예로 들어보겠습니다.

N = 3
8, 24, 9 각각을 소인수 분해합니다.
8 = 2 x 2 x 2
24 = 2 x 2 x 2 x 3
9 = 3 x 3

8, 24에 2를 9에 떼어주고 9에 있는 3을 8에 떼어주면 공통된 소수는 2 x 2 x 3 = 12(GCD)가 되고
이때 총 3번 떼어줬으니 3회 시도입니다.

최대가 되는 GCD를 구하는 방법은 잘 생각해보면 N개의 수를 소인수 분해해서 나오는 각각의 소수 개수를 N으로 나누면 됩니다. (분배 효과)
2  : 6개 -> 3으로 나누면 -> 2개 -> 2 x 2
3 : 2개 -> 3으로 나누면 -> 1개 -> 3
따라서 GCD = 2 x 2 x 3

그리고 총 이동 횟수를 구하는 방법은
if(각각의 점수에서 각각의 소수의 등장 횟수) < (분배되야할 각 소수의 개수)
    총 이동 횟수 +=  (분배되야할 각 소수의 개수) -  (각각의 점수에서 각각의 소수의 등장 횟수)

배열은 전체에서 각 소수들이 몇 개가 사용됐는지 체크하는 1차원 배열 과 각 점수에서 몇 개의 소수가 사용됐는지 체크하는 2차원 배열 두 개가 필요합니다.
*/

#include <iostream>
#include <vector>
using namespace std;

#define MAX 1000000
bool isPrime[MAX + 1];
int visited[MAX + 1];


void SieveOfEratosthenes() {
    for (int i = 2; i <= MAX; i++) {
        isPrime[i] = true; // 처음에 모두 소수라고 가정
    }
    for (int i = 2; i * i <= MAX; i++) { //2 부터 sqrt(n) 까지
        if (!isPrime[i]) continue; //이미 지워진 수는 무시
        for (int j = i * i; j <= MAX; j += i) { // 자기자신을 제외한 배수를 모두
            isPrime[j] = false; // 지운다
        }
    }
}

int power(int x, int y) {
    int res = 1;
    while (y > 0) {
        if (y % 2 == 1) {
            res = res * x;
        }
        y /= 2;
        x = x * x;
    }
    return res;
}

int main(void) {
    SieveOfEratosthenes();
    int n;
    cin >> n;
    vector<int> plist;
    for (int i = 1; i <= MAX; i++) if (isPrime[i]) plist.push_back(i);
    vector<vector<int> > v(n, vector<int>(plist.size(), 0));

    for (int i = 0; i < n; i++) {
        int score;
        cin >> score;
        for (int j = 0; j < plist.size(); j++) {
            if (score == 1) break;
            while (score % plist[j] == 0) {
                score /= plist[j];
                visited[plist[j]]++; //전체 들어있는 소수의 개수
                v[i][j]++; // i번째 숫자에 사용되는 각 소수의 개수
            }
        }
    }
    int gcd = 1;
    int cnt = 0;
    for (int i = 0; i < plist.size(); i++) {
        int d = visited[plist[i]] / n; //최소로 분배되야할 각 소수의 개수
        for (int j = 0; j < n; j++) {
            if (v[j][i] < d) {
                cnt += d - v[j][i]; // 분배
            }
        }
        gcd *= power(plist[i], d);
    }
    cout << gcd << " " << cnt;

    return 0;
}