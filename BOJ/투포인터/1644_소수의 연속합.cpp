/*
에라토스테네스 체로 소수 걸러낸 다음 투 포인터 알고리즘으로 답을 찾으면 된다.
*/

/*
2021.05.04 다시 풀이.
투포인터의 핵심은 두 개 포인터를 잘 조절해서 언제 인덱스를 증가시킬지, 종료할지 인것 같다.
*/
#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <cstring>
#include <cmath>
using namespace std;

const int MAX = 4000000 + 1;
int N;
bool isPrime[MAX];
vector<int> v;

//에라토스테네스의 체
void eratosthenes() {
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    int sqrtn = int(sqrt(N));
    for (int i = 2; i <= sqrtn; ++i) {
        if (isPrime[i])
            for (int j = i * i; j <= N; j += i)
                isPrime[j] = false;
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;

    eratosthenes();

    //소수인 것만 따로 저장
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i])
            v.push_back(i);
    }

    int left = 0, right = 0;
    int sum = 0;
    int ret = 0;
    while (1) {
        //합이 N이상이면 left 조정
        if (sum >= N) {
            sum -= v[left++];
        }
        //right가 범위 넘어가면 종료
        else if (right == v.size())
            break;

        //합이 N미만이면 right 증가
        else {
            sum += v[right++];
        }

        //sum==N이면 성립
        if (sum == N) {
            ret++;
        }
    }

    cout << ret;

    return 0;
}

////////////////////////////////////////////////

#include <iostream>

using namespace std;
#define MAX 4000010
int arr[MAX];
int prime[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    //에라토스테네스의 체
    for (int i = 0; i <= 4000000; i++)
        arr[i] = i;

    for (int i = 2; i <= 4000000; i++) {
        if (arr[i] == 0)
            continue;
        for (int j = i + i; j <= 4000000; j += i)
            arr[j] = 0;
    }

    //prime배열에 소수저장
    int j = 0, p_idx = 0;
    for (int i = 2; i <= 4000000; i++) {
        if (arr[i] != 0)
            prime[j++] = arr[i];
    }

    //prime 배열의 마지막 인덱스 저장
    p_idx = j - 1;

    int result = 0, sum = 0, low = 0, high = 0;
    int min = 999999999;
    while (1) {
        //투 포인터 알고리즘
        //1. 현재 부분합이 n이상이거나 이미 high==p+idx이면 low++
        //2. 그렇지 않다면 high++
        //3. 부분합이 n이상인 경우 길이 체크. 
        //이미 high가 포인터 하나 앞서있기 때문에 (high-1)-low+1를 해야 길이 나옴
        if (sum >= n) {
            sum -= prime[low++];
        }
        else if (high == p_idx)
            break;
        else
            sum += prime[high++];

        if (sum == n)
            result++;
    }

    cout << result;
    return 0;
}