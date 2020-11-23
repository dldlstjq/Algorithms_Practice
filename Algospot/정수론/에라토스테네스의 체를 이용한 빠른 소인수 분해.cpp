/*
에라토스테네스의 체를 이용한 빠른 소인수 분해
*/


#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAX = 1000000;

int N; //소인수분해하고자 하는 수
//minFactor[i]=i의 가장 작은 소인수(i가 소수인 경우 자기 자신)
int minFactor[MAX];

//에라토스테네스의 체를 수행하면서 소인수분해를 위한 정보도 저장한다.
void eratosthenes2() {
    //1은 항상 예외 처리
    minFactor[0] = minFactor[1] = -1;
    //모든 숫자를 처음에는 소수로 표시해 둔다.
    for (int i = 2; i <= N; ++i)
        minFactor[i] = i;

    //에라토스테네스의 체 수행
    for (int i = 2; i <= sqrt(N); ++i) {
        if (minFactor[i] == i) {
            for (int j = i * i; j <= N; j += i) {
                //아직 약수를 본 적 없는 숫자인 경우 i를 써 둔다.
                if (minFactor[j] == j)
                    minFactor[j] = i;
            }
        }
    }
}

//2이상의 자연수 n을 소인수분해한 결과를 반환한다.
vector<int> factor(int n) {
    vector<int> ret;
    //n이 1이 될때까지 가장 작은 소인수로 나누기를 반복한다.
    while (n > 1) {
        ret.push_back(minFactor[n]);
        n /= minFactor[n];
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (cin >> N) {
        cout << N << " = ";
        eratosthenes2();
        vector<int> result;
        result = factor(N);
        for (int i = 0; i < result.size() - 1; i++)
            cout << result[i] << " * ";
        cout << result[result.size() - 1];
        cout << "\n";
    }

    return 0;
}