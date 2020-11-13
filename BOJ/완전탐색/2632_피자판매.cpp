/*
여러 풀이 방법이 있는데 제일 간단한 코드를 가져왔다.
피자를 선택하는 부분을 해결하지 못해 풀지 못했다.
*/

/*
1. n, m 제한이 1000이므로 모든 연속된 구간의 합 sum을 계산한다.
2. sum이 어떤 구간에 있는지는 중요하지 않고 몇개나 나올 수 있는지가 중요하므로
Acnt, Bcnt 배열을 각각 만들에 sum이라는 값이 몇번 나올 수 있는지를 저장한다.


3. 1, 2 과정은 피자 A와 B에 대해 중복되는 연산이므로 func 함수를 만들어서 중복코드를 줄인다.
4. func에서 sum을 구할 때 i를 구간의 크기로 잡는 피자 조각이 n개라면 1에서 n까지 돌아야 한다.
j는 시작 index로 정한다.최초 index 0부터 시작하는 i 구간만큼의 sum을 구한다.
그 뒤의 for문은 j를 옮겨가면서 앞에는 빼주고 뒤에는 더해주는 과정이다.
i가 최대 크기인 경우엔 이 과정은 break.

5. A, B 한개의 피자에서만 조각을 모두 가져올 수도 있으므로 func에서 sum을 구하는 도중에 답을 더해준다.

6. Acnt, Bcnt를 모두 구했으면 곱연산으로 경우의 수를 구한다.*/

#include <cstdio>

int k, n, m, A[1000], B[1000], Acnt[2000001], Bcnt[2000001], ret;

void func(int p, int arr[], int arrCnt[]) {
    for (int i = 1; i <= p; i++) {
        int sum = 0;
        for (int j = 0; j < i; j++) sum += arr[j];
        arrCnt[sum]++;
        if (sum == k) ret++;

        if (i == p) break;
        for (int j = 1; j < p; j++) {
            sum -= arr[j - 1];
            sum += arr[(j + i - 1) % p];
            arrCnt[sum]++;
            if (sum == k) ret++;
        }
    }
}

int main() {
    scanf("%d%d%d", &k, &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", &A[i]);
    for (int i = 0; i < m; i++) scanf("%d", &B[i]);

    func(n, A, Acnt);
    func(m, B, Bcnt);

    for (int i = 1; i < k; i++) {
        int j = k - i;
        ret += Acnt[i] * Bcnt[j];
    }
    printf("%d", ret);
}
