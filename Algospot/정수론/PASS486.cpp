/*
1부터 MAX까지 하나씩 다 찾아보는 방법이 시간초과가 날 것 같아 수행하지 않았는데
시간초과가 발생하지 않았다. 천만 이하이기 때문에 가능한 것으로 보인다.
만약 천만 이상이거나 수가 많을 경우 완전탐색으로는 시간초과가 날 것이다.
따라서 책의 방법대로 소인수분해를 응용해서 푸는게 좋을 것 같다.
*/

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX = 10000000;   //천만
int N;  //n개의 약수
int lo, hi; //범위

//divisor[i]=i의 약수의 개수
int divisor[MAX + 1];
//minFactor[i]=i의 가장 작은 소인수
int minFactor[MAX + 1];
//minFactorPower[i]=i의 소인수 분해에는 minFactor[i]의 몇 승이 포함되어 있는가?
int minFactorPower[MAX + 1];

//에라토스테네스의 체로 소인수분해 정보 저장
void erathosthenes() {
    //1은 항상 예외 처리
    minFactor[0] = minFactor[1] = -1;

    //모든 숫자를 처음에는 소수로 표시
    for (int i = 2; i <= MAX; ++i)
        minFactor[i] = i;

    //에라토스테네스의 체를 수행
    int sqrtn = int(sqrt(MAX));
    for (int i = 2; i <= sqrtn; ++i) {
        if (minFactor[i] == i) {
            for (int j = i * i; j <= MAX; j += i)
                //아직 약수를 본적 없는 숫자인 경우 i를 써 둔다
                if (minFactor[j] == j)
                    minFactor[j] = i;
        }
    }
}


void getFactorsSmart() {
    divisor[1] = 1;
    for (int n = 2; n <= MAX; ++n) {
        //소수인 경우 약수가 두 개 밖에 없다.
        if (minFactor[n] == n) {
            minFactorPower[n] = 1;
            divisor[n] = 2;
        }
        //소수가 아닌 경우, 가장 작은 소인수로 나눈 수(m)의
        //약수의 수를 응용해 n의 약수의 수를 찾는다.
        else {
            int p = minFactor[n];
            int m = n / p;
            //m이 p로 더이상 나누어 지지 않는 경우
            if (p != minFactor[m])
                minFactorPower[n] = 1;
            else
                minFactorPower[n] = minFactorPower[m] + 1;
            int a = minFactorPower[n];
            divisor[n] = (divisor[m] / a) * (a + 1);
        }
    }
}

//1부터 다 찾아보는 것
void getFactors() {
    memset(divisor, 0, sizeof(divisor));
    for (int i = 1; i <= MAX; ++i) {
        for (int j = i; j <= MAX; j += i) {
            divisor[j]++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;

    /*getFactors();*/
    erathosthenes();
    getFactorsSmart();

    while (c--) {
        cin >> N >> lo >> hi;

        int cnt = 0;
        for (int i = lo; i <= hi; ++i) {
            if (divisor[i] == N)
                cnt++;
        }
        cout << cnt << "\n";
    }

    return 0;
}