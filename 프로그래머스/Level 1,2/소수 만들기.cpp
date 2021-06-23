/*
세 개의 수를 골라 더한 값이 소수가 되는지 구해야 한다.
소수인것을 보아 에라토스테네스의 체를 썼고 3개의 수를 뽑는다는 것에 조합을 썼다.
문제 자체는 그렇게 어렵지 않았고 더 간단한 방법이 있나 다른 사람 풀이를 봤다.
다른 사람들 풀이도 조합이나 for문을 써서 3개의 수를 뽑아 에라토스테네스로 소수인지 확인했다.
*/

#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX = 50000 + 1;
bool isPrime[MAX];

void eratosthenes() {
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    int sqrtn = sqrt(MAX);
    for (int i = 2; i <= sqrtn; ++i) {
        if (isPrime[i])
            //i의 배수 j들에 대해 isPriem[j]=false로 둔다.
            //i*i미만의 배수는 이미 지워졌으므로 신경 쓰지 않는다.
            for (int j = i * i; j <= MAX; j += i)
                isPrime[j] = false;
    }
}

int solution(vector<int> nums) {
    int answer = 0;

    // 에라토스테네스의 체
    eratosthenes();

    vector<bool> v(nums.size(), false);
    for (int i = 0; i < 3; ++i)
        v[i] = true;

    // 조합을 이용해 3개 수만 뽑아 소수인지 확인
    do {
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (v[i])
                sum += nums[i];
        }

        if (isPrime[sum])
            answer++;
    } while (prev_permutation(v.begin(), v.end()));

    return answer;
}