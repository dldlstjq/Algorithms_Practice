/*
약수의 개수를 구하는 게 핵심이다.
내가 푼 풀이는 n이 있을 때 2~n-1 까지 반복하며 나누어 떨어지면 카운트를 계속 한다.
만약 나누어 떨어지지 않으면 나눈 수와 카운트를 페어로 저장한다.
이 때 나누어 떨어지면 n을 나눠줘야 하기 때문에 임시 변수 하나를 만들어서 그걸 사용해야 한다.
소인수와 지수를 구했다면 약수의 개수를 구해 더하거나 빼면 된다.
*/

#include <string>
#include <vector>

using namespace std;

int solution(int left, int right) {
    int answer = 0;

    for (int i = left; i <= right; ++i) {
        if (i == 1) {
            answer -= 1;
            continue;
        }

        vector<pair<int, int>> v;   // 소인수와 지수 저장
        int j = 2;
        int cnt = 0;
        int tmp = i;
        // 약수 개수 구함. 2부터 i-1까지 나눠서 소인수분해 함
        while (j < i) {
            // 나누어 진다면 카운트하고 tmp를 j로 나눔.
            if (tmp % j == 0) {
                cnt++;
                tmp /= j;
                continue;
            }
            else {
                // 나누어지지 않을때 카운트가 있다면 소인수인 j와 지수인 cnt를 페어로 저장
                // 그리고 j 증가, 카운트 초기화
                if (cnt != 0) {
                    v.push_back({ j, cnt });
                    cnt = 0;
                }
                j++;
            }


        }

        // v에 원소가 없다는 건 소수. 소수는 약수 개수가 2
        if (!v.size())
            answer += i;
        else {
            // 지수+1을 다 곱하면 약수의 개수
            int ret = 1;
            for (int k = 0; k < v.size(); ++k)
                ret *= v[k].second + 1;

            if (!(ret % 2))
                answer += i;
            else
                answer -= i;

        }
    }

    return answer;
}



//////////////////////////////////////////
// 비트를 이용한 풀이. 비트 이용은 진짜 활용이 어려운 것 같다.
int sign(int n, int count = 1) {
    for (int i = 1, last = n >> 1; i <= last; ++i) if (n % i == 0) ++count;
    return count & 1 ? -1 : 1;
}
int solution(int a, int b) { return a > b ? 0 : sign(a) * a + solution(a + 1, b); }